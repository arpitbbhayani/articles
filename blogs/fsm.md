Finite state machines are simulate sequential logic and some computer programs, Finite state machines can be used to model problems in many fields including mathematics, artificial intelligence, games, and linguistics. 

![fsm for ab*c](https://user-images.githubusercontent.com/4745789/79634655-84fe9180-8189-11ea-9b94-f9ee563394bf.png)

Application sof FSM
    Automata-based programming
    Event-driven finite-state machine
    Virtual finite-state machine
    State design pattern
    Compilers
    Systems
    Rule based triggers
    Step Workflows
Vending Machines
Pacman
TCP/IP

# Python Coroutines
In a Finite State Machine, with every input, the control transits from one state to another and modelling them with Python Coroutines is pretty simple and intuitive. So before diving into the implementation we dive take a look at what Generators and Coroutines are and how they fit into this scheme of things.

## Generators
Generators, in python, are resumable functions which keeps on yielding values as long as someone keeps asking for it. Generators do not store all the values in memory rather they generate the values on the fly and hence extremely memory efficient.

A fibonacci generator could be written as

```py
def fib():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a+b
```

Say, we want first 10 fibonacci number we call `next` function on the generator returned by `fib()`. Everytime the `next` is called, the control loops through the instructions and yields one value when the flow reaches the `yield a` statement within `fib` and the flow is passed on the callee. When the `next` is called the second time, the `fib` is resumed from the place where the control returned. `next` function helps you resume the egenerator.

```py
>>> fgen = fib()
>>> [next(fgen) for _ in range(10)]
[0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
```

Hence now one process could ask for 10 numbers while other could ask for 1000 but the `fib` will not be compuing all values and storing it in memoty rather it will compute and yield values one by one.

## Coroutines
Python coroutines are resumable functions that wait for 

Consume Values

```py
```

# Finite State Machine for Regex

# Implementation

## Prime decorator

```py
def prime(fn):
    def wrapper(*args, **kwargs):
        v = fn(*args, **kwargs)
        v.send(None)
        return v
    return wrapper
```

## FSM

```py
class RegexFSM:
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
