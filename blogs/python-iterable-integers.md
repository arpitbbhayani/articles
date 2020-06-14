Iterables in Python are objects and containers that could be stepped through one item at a time, usually using a `for ... in` loop. Not all objects can be iterated, for example - we cannot iterate an integer, it is a singular value. The best we can do here is iterate on a range of integers using the `range` type which helps us iterate through all integers in the range `[0, n)`.

Since integers, individualistically, are not iterable, when we try to do a `for x in 7`, it raises an exception stating `TypeError: 'int' object is not iterable`. So what if, we change the Python's source code and make integers iterable, say every time we do a `for x in 7`, instead of raising an exception it actually iterates through the values `[0, 7)`. In this essay, we would be going through exactly that and the entire agenda goes like this;

- What is a Python iterable?
- What is an iterator protocol?
- Changing Python's source code and make integers iterable, and
- Why it might be a bad idea to do so?

# Python Iterables

Any object that could be iterated is an Iterable in Python. The list has to be the most popular iterable out there and it finds its usage in almost every single Python application - directly or indirectly. Before even the first user command is executed, the Python interpreter, while booting up has already created `406` lists, for its internal usage.

In the example below, we see how a list `a` is iterated through using a `for ... in` loop and each element can be accessed via variable `x`. 

```python
>>> a = [2, 3, 5, 7, 11, 13]
>>> for x in a: print(x, end=" ")
2 3 5 7 11 13
```

Similar to `list`, `range` is a python type that allows us to iterate on integer values starting from `start` and going till `end` while stepping over `step` values at each time. `range` is most commonly used for implementing a C-like for loop in Python, as illustrated below. In the example below, the `for` loop iterates over a `range` that starts from `0`, goes till `7` with a step of  `1` and producing the sequence `[0, 7)`.

```python
# The range(0, 7, 1) will iterate through values 0 to 6 and every time
# it will increment the current value by 1 i.e. the step.
>>> for x in range(0, 7, 1): print(x, end=" ")
0 1 2 3 4 5 6
```

Apart from `list` and `range` other iterables are - `tuple`, `set`, `str`, `bytes`, `bytearray`, `memoryview`, and `dict`.  In Python, we can also create custom iterables by making objects and types follow the Iterator Protocol.

# Iterators and Iterator Protocol

Python, keeping things simple, defines iterable as any object that follows the Iterator Protocol; which means the object or a container implements the following functions

- `__iter__` - should return an iterator object having implemented the `__next__` method
- `__next__` - should return the next item of the iteration and if items are exhausted then raise a `StopIteration` exception.

So, in a gist, `__iter__` is something that makes any python object iterable; hence to make integers iterable we need to have `__iter__` function for integers.

# Iterable in CPython

The most used implementation of Python language is [CPython](https://github.com/python/cpython/) where the entire language is implemented in pure C language. Since we need to make changes to one of the core datatypes of Python, we will be modifying the CPython, add `__iter__` function to integers, and rebuild the binary. But before jumping into the core implementation, it is important to understand a few fundamentals.

## The `PyTypeObject`

Every object in Python is associated with a type and each [type](https://docs.python.org/3/c-api/typeobj.html#type-objects) is an instance of a struct named [PyTypeObject](https://docs.python.org/3/c-api/typeobj.html). A new instance of this structure is effectively a new type in python. This structure holds a few meta information and a bunch of C function pointers - each implementing a small segment of the type's functionality. Most of these "slots" in the structure are optional which could be filled by putting appropriate function pointers that drive the corresponding functionality.

## The `tp_iter` slot

Among all the slots available, the slot that interests us is the `tp_iter` slot which can hold a pointer to a function that returns an iterator object. This slot corresponds to the `__iter__` function which effectively makes any object iterable. A non `NULL` value of this slot indicates iterability. The `tp_iter` can hold function with the following signature

```cpp
PyObject * tp_iter(PyObject *);
```

Integers in Python have been implemented as long objects and its implementation can be found at [longobject.c](https://github.com/python/cpython/blob/master/Objects/longobject.c). The instance of `PyTypeObject` that defines integer/long type is `PyLong_Type` and has its `tp_iter` slot set to `0` i.e. `NULL` which asserts the fact that Integers in python are not iterable. A glimpse of `tp_iter` being `NULL` for integers is illustrated below

```cpp
PyTypeObject PyLong_Type = {
    ...

    "int",                                      /* tp_name */
    offsetof(PyLongObject, ob_digit),           /* tp_basicsize */
    sizeof(digit),                              /* tp_itemsize */
    ...
    0,                                          /* tp_iter */
    ...
};
```

This `NULL` value for `tp_iter` makes `int` object not iterable and hence if this slot was occupied by a function pointer with the aforementioned signature, this could well make any integer iterable.

# Implementing `long_iter`

We name the `tp_iter` function on integer type as `long_iter` which will return an iterator object that effectively makes integers iterable. The core functionality we are looking to implement here is - when an integer `n` is iterated, it should iterate through the sequence `[0, n)` with step `1`. This behavior is very close to the pre-defined `range` type, that iterates over a range of integer values, more specifically a `range` that starts at `0`, goes till `n` with a step of `1`.

We define a utility function in `rangeobject.c` that given a python integer returns an instance of `longrangeiterobject` as per our specifications. This utility function will instantiate the `longrangeiterobject` with start as `0`, end as the long value given in the argument, and step as `1`. The utility function is as illustrated below.

```cpp
/*
 *  PyLongRangeIter_ZeroToN creates and returns a range iterator on long
 *  iterating on values in the range [0, n).
 *
 *  The function creates and returns a range iterator from 0 till the
 *  provided long value.
 */
PyObject *
PyLongRangeIter_ZeroToN(PyObject *long_obj)
{
		// creating a new instance of longrangeiterobject
    longrangeiterobject *it;
    it = PyObject_New(longrangeiterobject, &PyLongRangeIter_Type);

		// if unable to allocate memoty to it, return NULL.
    if (it == NULL)
        return NULL;

		// we set the start to 0
    it->start = _PyLong_Zero;

    // we set the step to 1
    it->step = _PyLong_One;
		
		// we set the index to 0, since we want to always start from the first
    // element of the iteration
    it->index = _PyLong_Zero;

    // we set the total length of iteration to be equal to the provided value
		it->len = long_obj;

		// we increment the reference count for each of the values referenced
    Py_INCREF(it->start);
    Py_INCREF(it->step);
    Py_INCREF(it->len);
    Py_INCREF(it->index);

    // downcast the iterator instance to PyObject and return
    return (PyObject *)it;
}
```

The utility function `PyLongRangeIter_ZeroToN` is defined in `rangeobject.c` and will be declared in `rangeobject.h` so that it can be used across the CPython. Declaration of function in `rangeobject.h` using standard Python macros goes like this

```cpp
PyAPI_FUNC(PyObject *)   PyLongRangeIter_ZeroToN(PyObject *);
```

The function occupying the `tp_iter` slot will receive the `self` object as the input argument and returns the iterator instance. Hence, the `long_iter` function will receive the python integer object (self) that is being iterated as an input argument and it should return the iterator instance. Here we would use the utility function `PyLongRangeIter_ZeroToN`, we just defined, and the entire function could be defined as

```cpp
/*
 *  long_iter creates an instance of range iterator using PyLongRangeIter_ZeroToN
 *  and returns the iterator instance.
 *
 *  The argument to the `tp_iter` is the `self` object and since we are trying to
 *  iterate an integer here, the input argument to `long_iter` will be the
 *  PyObject of type PyLong_Type, holding the integer value.
 */
static PyObject * long_iter(PyObject *long_obj)
{
    return PyLongRangeIter_ZeroToN(long_obj);
}
```

Now that we have `long_iter` defined, we can place the function on the `tp_iter` slot of `PyLong_Type` that enables the required iterability on integers.

```cpp
PyTypeObject PyLong_Type = {
    ...

    "int",                                      /* tp_name */
    offsetof(PyLongObject, ob_digit),           /* tp_basicsize */
    sizeof(digit),                              /* tp_itemsize */
    ...
    long_iter,                                  /* tp_iter */
    ...
};
```

## Consolidated flow

Once we have everything in place, the entire flow goes like this

Every time a `for ... in` is invoked on an integer object, it would check the `tp_iter` of the `PyLongType` and since now it holds the function pointer `long_iter`, the same function will be invoked. This invocation will return an iterator object of type `longrangeiterobject` with a fixed start, index, and step values - which in pythonic terms is effectively a `range(0, n, 1)`.  Hence the `for x in 7` is inherently evaluated as `for x in range(0, 7, 1)` allowing us to iterate integers.

> These changes are hosted on a remote branch [cpython@02-long-iter](https://github.com/arpitbbhayani/cpython/tree/02-long-iter) and Pull request to a forked CPython can be found [here](https://github.com/arpitbbhayani/cpython/pull/7).

# Integer iteration in action

Once we build a new python binary with aforementioned changes, we can see iterable integers in actions. Now when we do `for x in 7`, instead of raising an exception, it actually iterates through values `[0, 7)`.

```cpp
>>> for i in 7: print(i, end=" ");
0 1 2 3 4 5 6

# Since integers are now iterable, we can create a list of [0, 7) like
>>> list(7)
[0, 1, 2, 3, 4, 5, 6]
```

# Why it is not a good idea

Although it seems fun to have iterable integers but is not that great of an idea. The core reason for this is it makes unpacking unpredictable. Unpacking is when you unpack an iterable and assign it to multiple variables. For example: `a, b = 3, 4` will assign 3 to a and 4 to b. So assigning `a, b = 7` should be an error because there is just one value on the right side and multiple on the left.

But after making integers iterable the statement `a, b = 7` is effectively `a, b = [0, 1, 2, 3, 4, 5, 6]` which means it raises `ValueError: too many values to unpack (expected 2)`.

But things would work just fine if we do `a, b = 2` as now the right-hand side has two values and left has two variables to hold. Thus two very similar statements result in two very different outcomes.

```python
>>> a, b = 7
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ValueError: too many values to unpack (expected 2)

>>> a, b = 2
>>> a, b
0, 1
```

# Conclusion

In this essay, we modified the Python's source code and made integers iterable. Even though it is not a good idea to do so, but it is fun to play around with the code and make changes in our favorite programming language. It helps us get a detailed idea about core python implementation and may pave the way to become a Python core developer. This is one of many articles in Python Internals series, others are - [How python implements super long integers?](https://arpitbhayani.me/blogs/super-long-integers), [Python Caches Integers](https://arpitbhayani.me/blogs/python-caches-integers).
