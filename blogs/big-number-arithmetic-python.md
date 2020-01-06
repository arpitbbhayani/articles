When you code in a low-level language like C, you worry about picking the right data type for your integer; at every step, you need to think if `int` would suffice or should you go for `long` or even higher to `long double`. But while coding in Python, you need not worry about these "trivial" things because python supports integers of any size.

In C language you cannot compute 2 ^ 20000

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


One of the most virtue of Python is its
Python supports a "bignum" integer type which can work with arbitrarily large numbers.

While in C you have to think about limits of a `int` or `long` datatype and worry about using `signed` or `unsigned` to further extend it w.r.t your use case, Python makes our lives much much simpler. It supports arbitrarily large numberswhich means you could also do arithmetic on numbers that are greater indicates that calculations are performed on numbers whose digits of precision are limited only by the available memory of the host system.

Even though python is implemented in C language, but still how it does this arithmetic?

Structure of a integer/long object for Python
```
struct _longobject {
    PyObject_VAR_HEAD
    digit ob_digit[1];
};
```

```
struct _longobject {
    PyVarObject ob_base;
    digit ob_digit[1];
};
```

```
typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size; /* Number of items in variable part */
} PyVarObject;
```