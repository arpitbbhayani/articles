An integer in Python is not a traditional 2, 4 or 8 byte implementation but rather it is implemented as an array of digits in base 2<sup>30</sup> which enables Python to support [super long integers](https://arpitbhayani.me/blogs/super-long-integers). Since there is no explicit limit on the size, working with integers in Python is extremely convinient and we need not worry about the overflows. This convinience comes at a cost of allocation being expensive and trivial operations like addition, multiplication, division being inefficient.

Each integer in python is implemented as a C structure as illustrated below.

```cpp
struct _longobject {
    ...
    Py_ssize_t    ob_refcnt;      // <--- holds reference count
    ...
    Py_ssize_t    ob_size;        // <--- holds number of digits
    digit         ob_digit[1];    // <--- holds the digits in base 2^30
};
```

It is observed that smaller integers in the range -5 to 256, are used very frequently as compared to other longer integers and hence to gain performance benefit Python preallocates this range of integers during initialization and makes them singleton and hence everytime a smaller integer value is referenced instead of allocating a new integer it passes the reference of the corresponding singleton.

Here is what [Python's official documentation]((https://docs.python.org/3/c-api/long.html#c.PyLong_FromLong)) says about this preallocation

> The current implementation keeps an array of integer objects for all integers between -5 and 256, when you create an int in that range you actually just get back a reference to the existing object.

In the CPython's [source code](https://github.com/python/cpython/) this optimization can be traced in the macro `IS_SMALL_INT` and the function [get_small_int](https://github.com/python/cpython/blob/master/Objects/longobject.c#L40) in [longobject.c](https://github.com/python/cpython/blob/master/Objects/longobject.c). This way python saves a lot of space and computation for commonly used integers.

# Verifying smaller integers are indeed singleton
For a CPython implementation the in-built [`id` function](https://docs.python.org/3/library/functions.html#id) returns the address of the object in memory. This means if the smaller integers are indeed singleton then the return value of two instances of same value should return the same memory address while multiple instances of larger values should return different ones; and this is indeed what we observe

```py
>>> x, y = 36, 36
>>> id(x) == id(y)
True


>>> x, y = 257, 257
>>> id(x) == id(y)
False
```

# Verifying if these integers are indeed referenced
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
