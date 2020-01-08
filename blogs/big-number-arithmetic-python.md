When you code in a low-level language like C, you worry about picking the right data type and qualifiers for your integers; at every step, you need to think if `int` would suffice or should you go for a `long` or even higher to a `long double`. But while coding in python, you need not worry about these "trivial" things because python supports integers of arbitrary size.

In C, when you try to compute 2<sup>20000</sup> using builtin `powl` function it gives you `inf` as the output.

```c
#include <stdio.h>
#include <math.h>

int main(void) {
  printf("%Lf\n", powl(2, 20000));
  return 0;
}

$ ./a.out
inf
```

But for python, it is a piece of cake 🎂

```
>>> 2 ** 20000
39802768403379665923543072061912024537047727804924259387134 ...
...
... 6021 digits long ...
...
6309376
```

Python must be doing something beautiful internally to support integers of arbitrary sizes and today we find out what's under the hood!

# How integers are defined in python?
An integer in Python is a C struct defined as following

```c
struct _longobject {
    PyObject_VAR_HEAD
    digit ob_digit[1];
};
```

`PyObject_VAR_HEAD` is a macro that expands into a `PyVarObject` that has the following structure

```c
typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size; /* Number of items in variable part */
} PyVarObject;
```

Other types that has `PyObject_VAR_HEAD` are
 - `PyBytesObject`
 - `PyTupleObject`
 - `PyListObject`

This indicates that an integer, just like a `tuple` or a `list`, is variable in length and this is our first insight into how it could support gigantically long integers. The `_longobject` after macro expansion could be roughly seen as

```c
struct _longobject {
    PyObject ob_base;
    Py_ssize_t ob_size; /* Number of items in variable part */
    digit ob_digit[1];
};
```

> These are some meta fields in the `PyObject` struct, used for reference counting (garbage collection), but that we would require a separate article. The field that we will focus on is `ob_digit` and to some extent `ob_size`.

### Decoding `ob_digit`

`ob_digit` is an array of type `digit`, typedef'ed from `uint32_t`, statically allocated to size `1`. Since it is an array, `ob_digit` primarily is a `digit *`, pointer to `digit`, and hence if required could be malloced to any length. This makes it possible for python to represent and handle gigantically long integers.

Generally, In low-level languages like C, the precision of integers is limited to 64-bit, but Python implements [Arbitrary-precision integers](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic). Since Python 3 all integers are represented as a bignum and these are limited only by the available memory of the host system.

### Decoding `ob_size`
`ob_size` holds the count of elements in `ob_digit`. To be more efficient while allocating memory to array `ob_digit`, python overprovisions and then relies on `ob_size` to hold the actual number of elements in use.

# Understanding storage of integers

A naive way to store an integer digit-wise is by actually storing a decimal digit in one item of the array and then performing operations like addition subtraction will be like school maths.

With this approach, a number `5238` will be stored as

![representation of 5238 in a naive way](https://user-images.githubusercontent.com/4745789/71915727-5e03ed00-31a2-11ea-99c1-cdf28e74b595.png)

This approach is inefficient as we will be using up 32 bits to store a decimal digit that actually ranges only from 0 to 9 and could have been easily represented by mere 4 bits, and while writing something as versatile as python, a core developer has to be more resourceful.

So, can we do better? for sure, otherwise, this article should hold no place on the internet. Let's dive into how python actually stores a super long integer.

## The pythonic way

Instead of storing just one decimal digit in each item of the array `ob_digit`, python converts the number from base 10 to base 2<sup>30</sup> and calls each of element as `digit` which ranges from 0 to 2<sup>30</sup> - 1.

> Depending on the platform, Python uses either 32-bit unsigned integer arrays with 30-bit digits or 16-bit unsigned integer arrays with 15-bit digits. It requires a couple of bits to perform operations that will be discussed in some future articles.

### Lets see how python stores a number like 1152921504606846976

As for mentioned for Python "digit" is base 2<sup>30</sup> hence if you convert `1152921504606846976` you get `001`.

__1152921504606846976__ = __0__ * 2<sup>30<sup>0</sup></sup> + __0__ * 2<sup>30<sup>1</sup></sup> + __1__ * 2<sup>30<sup>2</sup></sup>

The `_longobject` struct for this value will hold

 - `ob_size` as `3`
 - `ob_digit` as `[0, 0, 1]`

![representation of 1152921504606846976 in a pythonic way](https://user-images.githubusercontent.com/4745789/71915782-7a078e80-31a2-11ea-8da6-6e86197ad5a7.png)

I have created a [demo REPL]((https://repl.it/@arpitbbhayani/super-long-int?language=python3)) that will output how python is storing integers internally and creates reference points for all struct members like `ob_size`, `ob_refcount`, etc.

# Operations on super long integers

Now that we have a fair idea on how integers in python are arbitrary precision integers and their persistence we should also understand how various mathematical operations happen on them.

## Addition

Integers are persisted "digit-wise", this means addition is just like how we used to do in school. The function named [x_add](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L3116) in file [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c] performs addition of two numbers.

```c
...
    for (i = 0; i < size_b; ++i) {
        carry += a->ob_digit[i] + b->ob_digit[i];
        z->ob_digit[i] = carry & PyLong_MASK;
        carry >>= PyLong_SHIFT;
    }
    for (; i < size_a; ++i) {
        carry += a->ob_digit[i];
        z->ob_digit[i] = carry & PyLong_MASK;
        carry >>= PyLong_SHIFT;
    }
    z->ob_digit[i] = carry;
...
```

The code snippet above is taken from `x_add` function and you could see how it actually iterates over the digits and performs addition and computes and propagates carry. Just the way we did it in school.

> The sign of the integer is the sign of `ob_size` which means, if you have a negative number then `ob_size` will be negative. The absolute value of `ob_size` will determine the number of digits in `ob_digit`.

## Subtaction

Similar to how addition is implemented, subtraction also happens the way we did it in school. The function named [x_sub](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L3150) in file [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c] performs subtraction of two numbers.

```c
...
    for (i = 0; i < size_b; ++i) {
        /* The following assumes unsigned arithmetic
           works module 2**N for some N>PyLong_SHIFT. */
        borrow = a->ob_digit[i] - b->ob_digit[i] - borrow;
        z->ob_digit[i] = borrow & PyLong_MASK;
        borrow >>= PyLong_SHIFT;
        borrow &= 1; /* Keep only one sign bit */
    }
    for (; i < size_a; ++i) {
        borrow = a->ob_digit[i] - borrow;
        z->ob_digit[i] = borrow & PyLong_MASK;
        borrow >>= PyLong_SHIFT;
        borrow &= 1; /* Keep only one sign bit */
    }
...
```

The code snippet above is taken from `x_sub` function and you could see how it actually iterates over the digits and performs subtraction and computes and propagates burrow.

## Multiplication

Again a naive way to implement multiplication will be what we learned in school math but it won't be very efficient. Python, in order to keep things efficient implements the [Karatsuba algorithm](https://en.wikipedia.org/wiki/Karatsuba_algorithm) that multiplies two n-digit numbers in O ( n<sup>log<sub>2</sub>3</sup> ) elementary steps.

The algorithm is slightly complicated is out of the scope of this article  but you can find its implementation in [k_mul](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L3397) and
[k_lopsided_mul](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c#L3618) functions in file [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c].

## Division and other operations

All operations on integers are defined in the file [longobject.c](https://github.com/arpitbbhayani/cpython/blob/0-base/Objects/longobject.c] and it is extremely simple to locate each one. Warning: it will take some time to understand each one in detail so grab some popcorn before you start reading.

# Optimization of commonly-used integers

Small integer objects in a range of -5 to 256 are always pre-allocated during initialization. Because Python integers are immutable, we can use them as singletons. Every time you need to create small integer instead of creating new object Python just points to already allocated one. Thereby it saves a lot of space and computation for commonly-used integers.

# Space inefficiency

Interestingly enough, the PyLongObject structure takes at least 28 bytes for every allocated integer and therefore takes three times as much memory as a simple 64-bit C integer.

# Conclusion