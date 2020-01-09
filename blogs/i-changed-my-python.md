Did you ever take a peek at Python's source code? I didn't and hence I decided to have some fun with it this week. After cloning the repository I realized how well written is the code that makes python what it is. In the process of exploring the codebase, I thought of making some changes, not big optimizations but some minor tweaks that will help me understand how Python is implemented in C and along the course learn some internals. To make things fun and interesting I thought of changing how addition work by making it incorrect and unpredictable which means `a + b` will internally do one of the following operations, at random

 - `a + b`
 - `a - b`
 - `a * b`
 - `a / b`
 - `a ** b`

After forking and cloning the source code of [python](https://github.com/python/cpython), I broke down the task into following sub-tasks

 - find the entry point (the main function) of python
 - find where addition happens
 - find how to call other perform operations like subtraction, multiplication, etc on python objects.
 - write a function that picks one of the operators at random
 - write a function that applies an operator on the two operands

Before getting into how I did it, take a look below and see what it does

![Random Math Operator in Python](https://user-images.githubusercontent.com/4745789/71643972-d96b2780-2ce6-11ea-894c-fd638dc95d7c.gif)

You would see how performing addition on numbers `4` and `6` evaluates to `0`, `10` and `24` depending on the operation it picked randomly.

> Note, the change I made will only work when one of the operands is a variable. If the entire expression contains constants then it will be evaluated as regular infix expression.

# Implementation
Operations in python work on opcodes very similar to the one that a microprocessor has. Depending on opcodes that the code is translated to, the operation is performed using operands (if required). The addition operation of python requires two operands and opcode is named `BINARY_ADD` and has value `23`. When the executor encounters this opcode, it fetches the two operands from top of the stack, performs addition and then pushes back the result on the stack. The code snippet below will give you a good idea of what python does when it encounters `BINARY_ADD`.

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

> One thing to observe here is how it concatenates when both operands are unicode/string.

### Checking if operands are numbers

For checking if both the operands for `BINARY_ADD` operation are numbers I used the predefined function named `PyNumber_Check` which checks if object referenced by `PyObject` is number or not.

```c
if (PyNumber_Check(left) && PyNumber_Check(right)) {
        // Both the operands are numbers
}
```

### Writing a random function
For generating random integer I used the current time in seconds from the system using `datetime.h` library and took modulus with the max value. The code snippet below picks a random number from `[0, max)`.

```c
int
get_random_number(int max) {
    return time(NULL) % max;
}
```

### Functions to perform other operations
Similar to the function `PyNumber_Add` which adds two python objects (if possible), there are functions named `PyNumber_Subtract`, `PyNumber_Multiply`, `PyNumber_FloorDivide`, and `PyNumber_Power` which performs operations as suggested by their names. I wrote a util function that takes two operands and an operator and returns the resulting python object after performing the required operation.

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

### The new `BINARY_ADD` implementation

Now as have everything required to make our `BINARY_ADD` unpredictable and following code snippet is very close to how it could be implemented.

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
After making all the required changes I ran `make` to build my new python binary and to my surprise, the code wouldn't build. The reason was that the function where I made the changes was called during build and initialization phases and due to incorrectness induced in the `BINARY_ADD` the process ended in __Segmentation Faults__ as now it has a function that instead of adding two numbers was subtracting, multiplying, dividing and raising to power at random.

To fix this issue I had to ensure that this random picking of operator only happened when the operation is asked from the interactive shell and should continue its normal execution for others. The function that gets called during an interactive shell is `PyRun_InteractiveLoopFlags` and hence I started passing a flag named `source` to all the functions till my trail reaches the opcode evaluation flow. The value of this `source` is set to `1` when it is triggered from the interactive shell for others the default value passed is `0`. Once I had this `source` field in place with the proper value being passed from various initiations, everything worked like a charm.

You can find the detailed diff at [github.com/arpitbbhayani/cpython/pull/1/files](https://github.com/arpitbbhayani/cpython/pull/1/files).

# Conclusion

It was fun to change the python's source code, I would recommend you to do this as well. It is always better if you know how things work internally and more importantly understand the complexities that are abstracted to make the application developers' experience seamless.

You can find the source code at [arpitbbhayani/cpython/tree/01-randomized-math-operators](https://github.com/arpitbbhayani/cpython/tree/01-randomized-math-operators). Feel free to fork it and make some changes of your own and share it with me. I will be thrilled to learn what you did with it.

If you want to dive deep into python's source I highly recommend you to read [realpython.com/cpython-source-code-guide/](https://realpython.com/cpython-source-code-guide/). It is an excellent guide to get you started and understand the language semantics and coding practices of a core python developer. Once you know the basics, navigating through the codebase is a walk in the park.
