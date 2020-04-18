Finite state machines is a mathematical model of computations thes helps us model sequential logic. FSM consists of finitie number of states, transitions, inputs alphabets (tokens), initial state and end state(s). FSM can be in exactly one of a finite number of states at any given time and it transitions into another state in response to some input. You can read more about FSM [here](https://en.wikipedia.org/wiki/Finite-state_machine).

In the field of computer science the FSMs are used in designing Compilers, Step worklows, Game Design, Protocols (like TCP/IP), event-driven programming, conversational AI and many more.

TODO EXAMPLE FSM

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
Python coroutines are resumable functions, just like generators but instead they consume values on the fly. The way we can do this is by using the `yield` statement as shown below

```py
def grep(pattern):
    while True:
        line = yield
        if pattern in line:
            print(line)
```

In the example above, the function

# Finite State Machine for Regex
Finite State Machine (FSM) for a regular expression `ab*c` could be designed as below

![fsm for ab*c](https://user-images.githubusercontent.com/4745789/79634655-84fe9180-8189-11ea-9b94-f9ee563394bf.png)

Each state of above FSM could be treated as an infinite loop waiting for an input, making the decision and doing the transition to the next state.

# Implementation
Each state of the FSM is modelled as a coroutine that holds its transition function and depending on input sent to the coroutine changes the current state.

## Low level modelling

### FSM Class

```py
class FSM:
    def __init__(self):
        self.current_state = None
        
        self.state_init = self._create_state_init()
        self.state_q1 = self._create_state_q1()
        self.state_q2 = self._create_state_q2()
        self.state_q3 = self._create_state_q3()
        
        self.current_state = self.state_init
        self.stopped = False
        
    def send(self, char):
        try:
            self.current_state.send(char)
        except StopIteration:
            self.stopped = True
        
    def does_match(self):
        if self.stopped:
            return Falset
        return self.current_state == self.state_q3

    @prime
    def _create_state_q1(self):
        while True:
            char = yield
            if char == 'b':
                self.current_state = self.state_q2
            elif char == 'c':
                self.current_state = self.state_q3
            else:
                break

    @prime
    def _create_state_q2(self):
        while True:
            char = yield
            if char == 'b':
                self.current_state = self.state_q2
            elif char == 'c':
                self.current_state = self.state_q3
            else:
                break

    @prime
    def _create_state_q3(self):
        while True:
            char = yield
            break

    @prime
    def _create_state_init(self):
        while True:
            char = yield
            if char == 'a':
                self.current_state = self.state_q1
            else:
                break
```

## Runner

```py
def grep_regex(text):
    evaluator = RegexFSM()
    for ch in text:
        evaluator.send(ch)
    return evaluator.does_match()
```

```py
>>> grep_regex("abc")
True

>>> grep_regex("aba")
False
```

# More Examples

## Divisibility by 3

![div3](https://user-images.githubusercontent.com/4745789/79635520-1290b000-818f-11ea-93ae-e2d1a4fc1e0b.png)

https://github.com/arpitbbhayani/fsm/blob/master/divisibility-by-3.ipynb

```py
@prime
def _create_state_q1(self):
    while True:
        digit = yield
        if  digit in [0, 3, 6, 9]:
            self.current_state = self.state_q1
        elif  digit in [1, 4, 7]:
            self.current_state = self.state_q2
        elif  digit in [2, 5, 8]:
            self.current_state = self.state_q0
```

## SQL Query Validator

![sql](https://user-images.githubusercontent.com/4745789/79635523-1c1a1800-818f-11ea-8afe-fe8065b55791.png)

https://github.com/arpitbbhayani/fsm/blob/master/sql-query-validator.ipynb

```py
@prime
def _create_state_explicit_cols(self):
    while True:
        token = yield
        if token == 'from':
            self.current_state = self.state_from_clause
        elif token == ',':
            self.current_state = self.state_more_cols
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
