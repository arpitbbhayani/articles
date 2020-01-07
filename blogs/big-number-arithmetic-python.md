When you code in a low-level language like C, you worry about picking the right data type for your integer; at every step, you need to think if `int` would suffice or should you go for `long` or even higher to `long double`. But while coding in Python, you need not worry about these "trivial" things because python supports integers of any size.

In C language you cannot compute   2<sup>20000</sup>, when you try it gives you `inf` as the output.

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

But for Python, it is a piece of cake 🎂

```
>>> 2 ** 20000
39802768403379665923543072061912024537047727804924259387134 ...
...
... 6021 digits long ...
...
6309376
```

Python must be doing something beautiful internally to support integers of any size and today we find out what's under the hood!

# Representation of integer in Python
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

This indicates that the integer object, just like a `tuple` or a `list`, is variable in length and gives us our first insight into how it could support gigantically long integers. The `_longobject` now roughly is represented as

```c
struct _longobject {
    PyObject ob_base;
    Py_ssize_t ob_size; /* Number of items in variable part */
    digit ob_digit[1];
};
```

> These are some meta fields in the `PyObject` struct but that we shall discuss some time in the future. The field that we will focus on is `ob_digit[1]`.


### Decoding `digit ob_digit[1];`

`ob_digit` is an array of `digit`, typedef'ed from `uint32_t`, by statically allocating size of `1` item and if required could be malloced to any length.

Generally, In low-level languages like C, the precision of integers is limited to 64-bit, but Python has built-in support for [Arbitrary-precision integers](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic). Since Python 3 all integers are represented as a bignum and these are limited only by the available memory of the host system.

# Understanding storage of integers

A naive way to store an integer digit-wise is by actually storing a decimal digit in one item of the array and then performing operations like addition subtraction will be like high school maths.

With this approach, a number `5238` will be stored as

![representation of 5238 in a naive way](https://user-images.githubusercontent.com/4745789/71900621-28e8a200-3184-11ea-9132-ccdf4e00ec44.png)

This approach is highly inefficient as we will be using up 32 bits of space to store a decimal digit that actually ranges only from 0 to 9 and could have been easily represented by mere 4 bits, and wasting 28 bits.

Can we do better? yes, and Python is doing it. Instead of storing just one decimal digit in each item of array `ob_digit`, python converts the number from base 10 to base 2<sup>30</sup> and calls each of element as `digit` which ranges from 0 to 2<sup>30</sup> - 1.

> Depending on the platform, Python uses either 32-bit unsigned integer arrays with 30-bit digits or 16-bit unsigned integer arrays with 15-bit digits.

# TODO: Why python does not use up all 32 bits?

For example, take a look at the x_add function (which actually adds the numbers, as opposed to long_add which sets up the call to x_add or x_sub):

Using such approach introduces additional requirements, that's why we can't use all bits of the integer.

To eliminate unnecessary computation CPython has a "fast path" implementation for integers in a range of −230
to 230

. Such integers are stored as an array of one element and if it's possible treated as fixed 32-bit integers.

Note that, unlike classical approach, the sign of an integer is stored separately in ob_size field. This field stores the size of the ob_digit array. So if you want to change the sign of an array of size 2 you need to set ob_size to -2.

The comment from the source code describes it as follows:

/* Long integer representation.
   The absolute value of a number is equal to
    SUM(for i=0 through abs(ob_size)-1) ob_digit[i] * 2**(SHIFT*i)
   Negative numbers are represented with ob_size < 0;
   zero is represented by ob_size == 0.
   In a normalized number, ob_digit[abs(ob_size)-1] (the most significant
   digit) is never zero.  Also, in all cases, for all valid i,
    0 <= ob_digit[i] <= MASK.
   The allocation function takes care of allocating extra memory
   so that ob_digit[0] ... ob_digit[abs(ob_size)-1] are actually available.

   CAUTION:  Generic code manipulating subtypes of PyVarObject has to aware that integers abuse  ob_size's sign bit.
*/

The representation of 123456789101112131415 will look as follows:
ob_size	3
ob_digit	437976919	87719511	107


Algorithm of converting our representation back:
(437976919∗230∗0)+(87719511∗230∗1)+(107∗230∗2)

```
import ctypes

class PyLongObject(ctypes.Structure):
    _fields_ = [("ob_refcnt", ctypes.c_long),
                ("ob_type", ctypes.c_void_p),
                ("ob_size", ctypes.c_ulong),
                ("ob_digit", ctypes.c_uint * 3)]


bignum = 18446744073709551615

for d in PyLongObject.from_address(id(bignum)).ob_digit:
    print(d)
```

# How different operations fare

### Addition

show malloc and point.

### Subtaction

show malloc and point.

### Multiplication

show malloc and point.
Karatsuba algorithm instead of the grade school algorithm if the numbers are big enough. (Because it's faster.) See the k_lopsided_mul functions.



Optimization of commonly-used integers

Small integer objects in a range of -5 to 256 are always pre-allocated during initialization. Because Python integers are immutable, we can use them as singletons. Every time you need to create small integer instead of creating new object Python just points to already allocated one. Thereby it saves a lot of space and computation for commonly-used integers.

Interestingly enough, the PyLongObject structure takes at least 28 bytes for every allocated integer and therefore takes three times as much memory as a simple 64-bit C integer.
