An integer in Python is not a traditional 2, 4 or 8 byte implementation but rather it is implemented as an array of digits in base 2<sup>30</sup> which enables Python to support [super long integers](https://arpitbhayani.me/blogs/super-long-integers). Since there is no explicit limit on the size, working with integers in Python is extremely convinient and we need not worry about the overflows. This convinience comes at a cost of allocation being expensive and trivial operations like addition, multiplication, division being inefficient.

Each integer in python is implemented as a C structure as illustrated

```cpp
struct _longobject {
    ...
    Py_ssize_t    ob_refcnt;      // <--- holds reference count
    ...
    Py_ssize_t    ob_size;        // <--- holds number of digits
    digit         ob_digit[1];    // <--- holds the digits in base 2^30
};
```

It is observed that smaller integers, -5 to 256, are used very frequently as compared to other longer integers and hence to gain performance benefit Python preallocates this range of integers during initialization and makes them singleton and hence everytime the integer value is referenced instead of allocating a new integer it passes the reference of the corresponding singleton.

Here is what [official Python documentation]((https://docs.python.org/3/c-api/long.html#c.PyLong_FromLong)) says about preallocation

> The current implementation keeps an array of integer objects for all integers between -5 and 256, when you create an int in that range you actually just get back a reference to the existing object. So it should be possible to change the value of 1. I suspect the behaviour of Python in this case is undefined. :-)

This optimization can be traced in the macro `IS_SMALL_INT` and the function [get_small_int](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L43) in [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L35). This way python saves a lot of space and computation for commonly used integers.

We can see this in action by using `id` function

For CPython, the `id` function returns the memory address the variable or value points to and we can use this to check if applying `id` function on smaller integers vs larger integers yields us same of different values.

```py
>>> x, y = 36, 36
>>> id(x) == id(y)
True


>>> x, y = 257, 257
>>> id(x) == id(y)
False
```

# Reference Counts of Integers
Now that we have established that Python indeed is using smaller integers by reference and not reallocating them, it time we check exactly how much Python saves by doing this. This we could do by finding reference counts of each of 256 integers and

https://docs.python.org/3/c-api/intro.html#objects-types-and-reference-counts

```py
>>> ref_count = sys.getrefcount(50)
32131
```

When we do this for all integers in range -5 to 1000 we get the following distribution

[loglog graph](https://user-images.githubusercontent.com/4745789/82136535-b15f0980-982c-11ea-9dcb-2da98e8fc9ea.png)

## What does this mean?

Python during initialization requires integer objects and most of these objects are in range -5 to 256. To make initialization faster Python caches the interger objects.

In usual programming the most common integer values used are in fact in the range -5 to 256 and by caching the referece and using them as singleton this could be optimized.

# References
 - [Why Python is Slow: Looking Under the Hood](http://jakevdp.github.io/blog/2014/05/09/why-python-is-slow/)
