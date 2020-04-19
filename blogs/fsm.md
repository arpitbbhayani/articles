Finite state machines is a mathematical model of computations to model sequential logic. FSM consists of finite number of states, transition function, inputs alphabets, start state and end state(s). In the field of computer science the FSMs are used in designing Compilers, Linguistics, Step workflows, Game Design, Protocols Procedures (like TCP/IP), Event-driven programming, Conversational AI and many more.

A finite state machine that simulates a Traffic Signal is designed below. `Green` is the start/initial state, which upon receiving a trigger moves to `Yellow` state, which upon receiving a trigger transitions to `Red` state. The `Red` state circles back to `Green` and the loop continues. The machine does not have any end state because we do not want our traffic signal to stop functioning. 

![traffic signal fsm](https://user-images.githubusercontent.com/4745789/79678813-d572ff00-821c-11ea-8437-b4a3b7fd1a60.png)

Any FSM can be in exactly one of a finite states at any given time and it transitions into another state in response to some input. In the example above, at any point in time the traffic signal is exactly in one state - either `Green`, `Yellow` or `Red`. The transition rules are defined for each state and because of that rules we will always see `Red` going back to `Green` and never `Yellow`. Thus transition function defines the rules which the state and the FSM adheres to and is the one that determines the sequential loigc the FSM builds.

In this article we will dive deep into how we can model a finite state machine using Python coroutines.

# Python Coroutines
In a Finite State Machine, with every input, the control transits from one state to another and modelling them with Python Coroutines is simple and intuitive. So before diving into the implementation we take a detour and look at what Generators and Coroutines are and how they fit into this scheme of things.

## Generators
Generators, in python, are **resumable functions** which keeps on yielding values as long as someone keeps asking for the new values, by calling `next` function on it. If there are no more values to yield, generators raise a `StopIteration` excetpion.

```py
def fib():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a+b
```

The `yield` statement is the one where the magic happens. yielded value is returned to the caller and the function execution is paused and the caller continues its execution. The flow returns back to the generator when the caller function asks from the next value. Once the next value is requested by calling `next`, the generator function resumes from where it left off i.e. `yield` statement.

```py
>>> fgen = fib()
>>> [next(fgen) for _ in range(10)]
[0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
```

Thus using a fibonacci generator is extremely memory efficient as now we need not compute a lot of fibonacci numbers and hold them in memory, rather the process could ask for as many values as it needs and the generator would keep on yielding values one by one.

## Coroutines
Coroutines are resumable functions, just like generators, but instead they consume values on the fly. The working of it is very similar to generator and again the `yield` statement is where the magic happens. When a coroutine is paused at the `yield` statement, we could send the value it using `send` function and the value could be used using assignment operator on `yield` as shown below

```py
def grep(substr):
    while True:
        line = yield
        if substr in line:
            print(f"found {substr}")
```

In the example above, when the generator `grep` is paused at the `yield` statement, we could send the value to it and the value we send will be stored in the variable `line`.

> Before sending the value to a coroutine we need to "prime" it so that the flow reaches the yield statement and is paused, at the yield statement, and is ready to accept values.

```py
>>> g = grep("users/created")
>>> next(g)  # priming the generator
>>>
>>> g.send("users/get api took 1 ms.")
>>> g.send("users/created api took 3 ms.")
found users/created
>>> g.send("users/get api took 1 ms.")
>>> g.send("users/created api took 4 ms.")
found users/created
>>> g.send("users/get api took 1 ms.")
```

In the example above we see how we have written a simple `grep` function that as and when receives input resumes its execution and spits out if the input `line` contains the substring `substr` in it. We need not pass all the lines to the grep function at once rather we can "stream" the lines as and when we see it to this grep function and it would print as and when it finds `substr` in the `line`.

The ability of coroutines to pause the execution and accept input on the fly helps us model FSM in an extremely intuitive way.

# Building a Finite State Machine
As mentioned above a finite state machine contains finite number of states, transition function, inputs, initial state and end state. The machine at a point in time is in one of the finite states and upon receiving an input, it transitions to the next state as determined by the transition function.

The way we are using states is oddly similar to how Python Coroutines work, hence we can model a state as a Python co-routine that runs an infinite loop within which it accepts the input, decides the transition and changes the current state of the FSM.

To dive into low level details, we build an FSM for a regular expression `ab*c`. The FSM for the regular expression looks something like this, take a note of the transitions between states.

![fsm for ab*c](https://user-images.githubusercontent.com/4745789/79634655-84fe9180-8189-11ea-9b94-f9ee563394bf.png)

## State
Each state is modelled as an infinitely running coroutine which on receiving an input, makes the decision and changes the state of the machine. From the FSM defined for the regex `ab*c`, we could write the model the state `q2` as shown below

```py
def _create_q2():
    while True:
        # Wait till the input is received.
        # once received store the input in `char`
        char = yield

        # depending on what we received as the input
        # change the current state of the fsm
        if char == 'b':
            # on receiving `b` the state moves to `q2`
            current_state = q2
        elif char == 'c':
            # on receiving `c` the state moves to `q3`
            current_state = q3
        else:
            # on receiving any other input, break the loop
            # so that next time when someone sends any input to
            # the coroutine it raises StopIteration
            break
```

## FSM Class
To keep things encapsulated we will define a class for FSM which holds all the states and maintains current state of the machine. It will also have a method called `send` which actually sends input to the current state. The current state upon receiving this input, makes a decision and updates the `current_state` of the FSM.

Depending on the usecase the FSM could also have a function that answers the core problem statemet, example does the given line matches the regular expression? or is the number divisible by 3?

The FSM class for the regular expression `ab*c` could be modelled as,

```py
class FSM:
    def __init__(self):
        # initializing states
        self.start = self._create_start()
        self.q1 = self._create_q1()
        self.q2 = self._create_q2()
        self.q3 = self._create_q3()
        
        # setting current state of the system
        self.current_state = self.start

        # stopped flag to denote that iteration is stopped due to bad
        # input against which transition was not defined.
        self.stopped = False

    def send(self, char):
        """The function sends the curretn input to the current state
        It captures the StopIteration exception and marks the stopped flag.
        """
        try:
            self.current_state.send(char)
        except StopIteration:
            self.stopped = True
        
    def does_match(self):
        """The function at any point in time returns if till the current input
        the string matches the given regular expression.

        It does so by comparing the current state with the end state `q3`.
        It also checks for `stopped` flag which sees that due to bad input
        the iteration of FSM had to be stopped.
        """
        if self.stopped:
            return False
        return self.current_state == self.q3

    ...
    
    @prime
    def _create_q2(self):
        while True:
            # Wait till the input is received.
            # once received store the input in `char`
            char = yield

            # depending on what we received as the input
            # change the current state of the fsm
            if char == 'b':
                # on receiving `b` the state moves to `q2`
                self.current_state = self.q2
            elif char == 'c':
                # on receiving `c` the state moves to `q3`
                self.current_state = self.q3
            else:
                # on receiving any other input, break the loop
                # so that next time when someone sends any input to
                # the coroutine it raises StopIteration
                break
    ...

```

Similar to how we have defined the function `_create_q2` we could defined functions for the other three states `start`, `q1` and `q3`. You can find how it is defined at [arpitbbhayani/fsm/regex-1](https://github.com/arpitbbhayani/fsm/blob/master/regex-1.ipynb)

## Running
The input to this FSM will be a stream of input characters, and for passing this input to the current state we have a function called `send` in the `FSM` class that in turn sends the data to the current state, implemented as coroutine. Once we have sent all the characters from the text to this `FSM` we call the helped function `does_match` which tells us if the text matches the pattern or not by checking it against the final end state of the FSM.

```py
def grep_regex(text):
    evaluator = FSM()
    for ch in text:
        evaluator.send(ch)
    return evaluator.does_match()

>>> grep_regex("abc")
True

>>> grep_regex("aba")
False
```

> The way we have implemented state, it is very natural to think that they are all running in parallel, like threads, but in reality the entire execution is pure sequential - and that's the magic of Coroutines. All states seems independent and seems to run in parallel instead all of them are executed in one thread concurrently using coroutines. The coroutines of the current state is executing while all others are suspended on their corresponding `yield` statements.

# More FSMs
We have seen how intuitive it is to build Regular expression FSMs using Python coroutines, but if our hypothesis is true things should equally intuitive when we are implementing FSMs for other use cases and here we take a look at two examples and see how a state coroutines is implemented in each

## Divisibility by 3
The FSM that tells if a given stream of digits constuiting a number is divisible by 3 or not, is designed as follows. The state `q0` is the end state that denotes remainder to be 0.

![div3](https://user-images.githubusercontent.com/4745789/79641628-564ae000-81b6-11ea-9c84-147cae3a30a6.png)

The state coroutines for state `q1` is implemented as below

```py
@prime
def _create_q1(self):
    while True:
        digit = yield
        if  digit in [0, 3, 6, 9]:
            self.current_state = self.q1
        elif  digit in [1, 4, 7]:
            self.current_state = self.q2
        elif  digit in [2, 5, 8]:
            self.current_state = self.q0
```

The similarity between the coroutine implemtation and transition function for a state is uncanny. The entire implementation of this FSM can be found at [arpitbbhayani/fsm/divisibility-by-3](https://github.com/arpitbbhayani/fsm/blob/master/divisibility-by-3.ipynb)

## SQL Query Validator

![sql](https://user-images.githubusercontent.com/4745789/79635523-1c1a1800-818f-11ea-8afe-fe8065b55791.png)

https://github.com/arpitbbhayani/fsm/blob/master/sql-query-validator.ipynb

```py
@prime
def _create_explicit_cols(self):
    while True:
        token = yield
        if token == 'from':
            self.current_state = self.from_clause
        elif token == ',':
            self.current_state = self.more_cols
        else:
            break
```

# Conclusion
Even though this may not be the most efficinet way to implement and build FSM but it is most intuitive way indeed. The edges and state transitions translate well into `if` and `elif`, each state is modelled as an independant co-routines and we still do things in a sequential manner. It feels parallel but it is infact sequential.

More like passing the parcel.

# References and Readings

 - [Finite State Machines - Brilliant.org](https://brilliant.org/wiki/finite-state-machines/)
 - [Finite State Machines - Wikipedia](https://en.wikipedia.org/wiki/Finite-state_machine)
 - [FSM Applications](https://web.cs.ucdavis.edu/~rogaway/classes/120/spring13/eric-applications.pdf)
 - [What Are Python Coroutines?](https://realpython.com/lessons/what-are-python-coroutines/)
 - [How to Use Generators and yield in Python](https://realpython.com/introduction-to-python-generators/)
