This week I decided to play with python's source code, the code that makes python what it is, and see how it is implemented and in the process learn some internals.  To make learning fun I decided to change how addition of two numbers work by adding randomness to it; which means when you perform `a + b` it will internally do one of the following operations

 - `a + b`
 - `a - b`
 - `a * b`
 - `a / b`
 - `a ** b`

Although this makes my python unpredictable and makes no sense, but all I wanted to do is understand the internals of it and have fun while doing it.

After forking and cloning the source code of [python](https://github.com/python/cpython), I broke down the task into following sub tasks

 - find the entry point (the main function) of python
 - find where addition happens
 - find how to call other perform operations like subtraction, multiplication, etc on python objects.
 - write a function that picks one of operators at random
 - write a function that applies an operator on the two operands

Before getting into how I did it, take a look below

![Random Math Operator in Python](https://user-images.githubusercontent.com/4745789/71643972-d96b2780-2ce6-11ea-894c-fd638dc95d7c.gif)

You would see how performing addition on numbers `4` and `6`, it evaluated to `0`, `10` and `24` depending on the operation it randomly picked to apply on it.

> The change I made will only work when one of the operand is a variable. If the entire expression contains constants then it will be evaluated as regular infix expression.

# Implementation
Operations in python works on opcodes similar to one that a microprocessor has. Depending on opcodes that the code is translated to, the operation is performed. For addition of two operands there is an opcode called `BINARY_ADD` and when the executor encounters this opcode, it fetches the two operands from top of the stack, performs addition and then pushes back the result on the stack.

```c
case TARGET(BINARY_ADD): {
    PyObject *right = POP();
    PyObject *left = TOP();
    PyObject *sum;
    if (PyUnicode_CheckExact(left) &&
             PyUnicode_CheckExact(right)) {
        sum = unicode_concatenate(tstate, left, right, f, next_instr);
    }
    else {
        sum = PyNumber_Add(left, right);
    }
    SET_TOP(sum);
    ...
}
```

> One thing to observe here is how python does concatenation when both operands are unicode/string.

### Checking if operands are numbers

For checking if both the operands for `BINARY_ADD` operation are numbers I found a function named `PyNumber_Check` which does exactly what I wanted.

```c
if (PyNumber_Check(left) && PyNumber_Check(right)) {
        // Both the operands are numbers
        // Do something
}
```

### Random Function
For randomizing, I used the current time in seconds from the system using `datetime.h` library and took modulus with the max value I wanted. Since I am picking one of 5 operators at random my random function looks like this

```c
int
get_random_number(int max) {
    return time(NULL) % max;
}
```

### Functions to perform other operations
Similar to the function `PyNumber_Add`, for adding two python objects, there are function named `PyNumber_Subtract`, `PyNumber_Multiply`, `PyNumber_FloorDivide`, and `PyNumber_Power` which performs operations as suggested by their names.

```c
PyObject *
binary_operate(PyObject * left, PyObject * right, char operator) {
    switch (operator) {
        case '+':
            return PyNumber_Add(left, right);
        case '-':
            return PyNumber_Subtract(left, right);
        case '*':
            return PyNumber_Multiply(left, right);
        case '/':
            return PyNumber_FloorDivide(left, right);
        case '^':
            return PyNumber_Power(left, right, Py_None);
        default:
            return NULL;
    }
}
```

The final `BINARY_ADD` implementation, with randomization, looks very similar to code snippet below

```c
case TARGET(BINARY_ADD): {
    PyObject *right = POP();
    PyObject *left = TOP();
    PyObject *result;
    if (PyUnicode_CheckExact(left) &&
             PyUnicode_CheckExact(right)) {
        result = unicode_concatenate(tstate, left, right, f, next_instr);
    }
    else {
        // Do this operation only when both the operands are numbers and
        // the evaluation was initiated from interactive interpreter (shell)
        if (PyNumber_Check(left) && PyNumber_Check(right)) {
            char operator = get_random_operator();
            result = binary_operate(left, right, operator);
            printf(
                "::::: %s + %s was evaluated as %s %c %s, hence to the value\n",
                ReprStr(left), ReprStr(right),
                ReprStr(left), operator, ReprStr(right)
            );
        } else {
            result = PyNumber_Add(left, right);
        }
        ...
    }
    ...
    SET_TOP(result);
    ...
}
```

# Challenges
As soon as I had everything I required, I started making changes and once I was done, I ran `make` to create my new python build and to my surprise, the code wouldn't build. It turned out that the function where I made the changes was called during build and initialization phases and due to my randomness now things started breaking due to __Segmentation Faults__ that it got when the function which was expected to add two numbers is now subtracting, multiplying, dividing at random.

To fix this issue I had to ensure that the randomness that I was adding should be added only when the operation is asked from an interactive shell and should do usual addition when called from any other source. Hence I traced the function that gets called during interactive shell, `PyRun_InteractiveLoopFlags`, and made changes to pass a flag called `source` to all the functions till my trail reaches the opcode evaluation flow. Once I had this `source` field in place, everything worked like a charm and I was able to randomly do subtraction, multiplication, division and power during addition.

You can find the detailed diff at [github.com/arpitbbhayani/cpython/pull/1/files](https://github.com/arpitbbhayani/cpython/pull/1/files).

# Conclusion

It was fun to change the python's source code, I would recommend you to do this as well. It is always better if you know how things work internally and more importantly understand the complexities that are abstracted to make python developer's experience seamless.

You can find the source code at [github.com/arpitbbhayani/cpython/tree/01-randomized-math-operators](https://github.com/arpitbbhayani/cpython/tree/01-randomized-math-operators). Feel free to fork it and make some changes of you own and share it with me. I will be thrilled to learn what you did with it.

If you want to dive deep into python's source I highly recommend you to read [realpython.com/cpython-source-code-guide/](https://realpython.com/cpython-source-code-guide/). It is an excellent guide to get you started and understand semantics and practices of core python developer. Once you know the basics, navigating through the codebase is a walk in the park.