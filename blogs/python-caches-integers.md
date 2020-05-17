python-caches-integers

# Optimization of commonly-used integers

Python [preallocates](https://docs.python.org/3/c-api/long.html#c.PyLong_FromLong) small integers in a range of -5 to 256. This allocation happens during initialization and since we cannot update integers (immutability) these preallocated integers are singletons and are directly referenced instead of reallocating. This means every time we use/creates a small integer, python instead of reallocating just returns the reference of preallocated one.

This optimization can be traced in the macro `IS_SMALL_INT` and the function [get_small_int](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L43) in [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L35). This way python saves a lot of space and computation for commonly used integers.

# References
