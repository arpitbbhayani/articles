An integer in Python is not traditional 2/4 or 8 byte implementation but rather an array of digits in base 2<sup>30</sup> which enables Python to support [super long integers](https://arpitbhayani.me/blogs/super-long-integers). Since there is no explicit limit on the size, working with Python integers is very convinient as now we need not worry about the overflows. This convinience comes at a cost of allocation being expensive and trivial opetaions like addition, multiplication being inefficient.

It is observed that smaller integers -5 to 256 are used very frequently as compared to other longer integers and hence to gain performance benefit Python preallocates this singleton range of integers during initialization and passes on the reference everytime the integer value is referenced.

Here is what [official Python documentation]((https://docs.python.org/3/c-api/long.html#c.PyLong_FromLong)) says about preallocation

> The current implementation keeps an array of integer objects for all integers between -5 and 256, when you create an int in that range you actually just get back a reference to the existing object. So it should be possible to change the value of 1. I suspect the behaviour of Python in this case is undefined. :-)

This optimization can be traced in the macro `IS_SMALL_INT` and the function [get_small_int](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L43) in [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L35). This way python saves a lot of space and computation for commonly used integers.

# References
