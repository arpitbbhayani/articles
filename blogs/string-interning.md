Every programming language aims to be performant in its niche and achieving superior performance requires a bunch of compiler and interpreter level optimizations. Since character Strings are an integral part of any programming language, having an ability to perform string operations quickly elevates the overall performance.

In this essay, we dive deep into Python internals and find out how Python makes its interpreter performant using a technique called [String Interning](https://en.wikipedia.org/wiki/String_interning). This essay not only aims to put forth Python internals but it also aims to make the reader comfortable in navigating through the Python's source code; so expect a lot of code snippets taken from [CPython](https://github.com/python/cpython/).

# String Interning

String Interning is a compiler/interpreter optimization method that makes common string processing tasks space and time efficient by [caching](https://en.wikipedia.org/wiki/Cache_(computing)) them. Instead of creating a new copy of string every time, this optimization method dictates to keep just one copy of string for every *appropriate* [immutable](https://en.wikipedia.org/wiki/Immutable_object) distinct value and use the pointer reference wherver referred.

The single copy of each string is called its ***intern*** and hence the name String Interning. The lookup of string intern, may or may not be exposed as a public interfaced method. Modern programming languages like Java, Python, PHP, Ruby, Julia, and many more, performs String Interning to make their compilers and interpreters performant.

![https://user-images.githubusercontent.com/4745789/102705512-d1691680-42ae-11eb-825f-1e032a7c12c5.png](https://user-images.githubusercontent.com/4745789/102705512-d1691680-42ae-11eb-825f-1e032a7c12c5.png)

## Why should Strings be interned?

*String Interning speeds up string comparisons*. Without interning if we were to compare two strings  for equality the complexity of it would shoot up to `O(n)` where we examine every character from both the strings to decide their equality. But if the strings are interned, instead of checking every character, equal strings will have the same object reference so just a pointer quality check would be sufficient to say if two string literals are equal. Since this is a very common operation, this is typically implemented as a pointer equality test, using just a single machine instruction with no memory reference at all.

*String Interning reduces the memory footprint.* If there are many instances of the same string value read from expensive source like Network or Disk, examples magic numbers or network protocol information. Instead of passing the string literals, we can pass references: example: Tag names in XML can be passed as references and thus saving time and memory footprint during serialization.

# String Interning in Python
Just like most other modern programming languages, Python also does [String Interning](https://en.wikipedia.org/wiki/String_interning) to gain a performance boost. In Python, we can find if two objects are referring to the same in-memory object using the `is` operator. So if two string objects refer to the same in-memory object, the `is` operator yields `True` ortherwise `False`.

```bash
>>> 'python' is 'python'
True
```

We can use this particular operator to test which all strings are interned and which are not. In CPython, String Interning is implemented through the following function, declared in [unicodeobject.h](https://github.com/python/cpython/blob/master/Include/unicodeobject.h) and defined in [unicodeobject.c](https://github.com/python/cpython/blob/master/Objects/unicodeobject.c).

```cpp
PyAPI_FUNC(void) PyUnicode_InternInPlace(PyObject **);
```

In order to check if a String is interned, CPython implements a macro named `PyUnicode_CHECK_INTERNED`, again defined in [unicodeobject.h](https://github.com/python/cpython/blob/master/Include/unicodeobject.h). The macro suggests that the Python maintains a member named `interned` in `PyASCIIObject` structure whose value suggests if the corresponding String is interned or not.

```cpp
#define PyUnicode_CHECK_INTERNED(op) \
    (((PyASCIIObject *)(op))->state.interned)
```

## Internals of String Interning

In CPython, the String references are stored, accessed, and managed using a Python dictionary named `interned`. This dictionary is lazily initialized upon the first String Intern invocation and holds the reference to all the interned String objects.

### Interning the String

The core function responsible for interning the String is named `PyUnicode_InternInPlace` defined in [unicodeobject.c](https://github.com/python/cpython/blob/master/Objects/unicodeobject.c) that upon invocation lazily builds the main dictionary `interned` to hold all interned strings and then registers the object into it with the key and the value both set as the same object reference. Following function snippet shows the String Interning process as implemented in Python.

```cpp
void
PyUnicode_InternInPlace(PyObject **p)
{
    PyObject *s = *p;

    .........

    // Lazily build the dictionary to hold interned Strings
    if (interned == NULL) {
        interned = PyDict_New();
        if (interned == NULL) {
            PyErr_Clear();
            return;
        }
    }

    PyObject *t;

    // Make an entry to the interned dictionary for the
    // given object
    t = PyDict_SetDefault(interned, s, s);

    .........
    
    // The two references in interned dict (key and value) are
    // not counted by refcnt.
    // unicode_dealloc() and _PyUnicode_ClearInterned() take
    // care of this.
    Py_SET_REFCNT(s, Py_REFCNT(s) - 2);

    // Set the state of the string to be INTERNED
    _PyUnicode_STATE(s).interned = SSTATE_INTERNED_MORTAL;
}
```

### Cleanup of Interned Strings

The cleanup function iterates over all the Strings held in the `interned` dictionary, adjusts the reference counts of the object, and marks them as `NOT_INTERNED` allowing them to be garbage collected. Once all the strings are marked as `NOT_INTERNED`, the `interned` dictionary is cleared and deleted. The cleanup function is defined in [unicodeobject.c](https://github.com/python/cpython/blob/master/Objects/unicodeobject.c) by the name `_PyUnicode_ClearInterned`.

```cpp
void
_PyUnicode_ClearInterned(PyThreadState *tstate)
{
    .........

    // Get all the keys to the interned dictionary
    PyObject *keys = PyDict_Keys(interned);

    .........

    // Interned Unicode strings are not forcibly deallocated;
    // rather, we give them their stolen references back
    // and then clear and DECREF the interned dict.

    for (Py_ssize_t i = 0; i < n; i++) {
        PyObject *s = PyList_GET_ITEM(keys, i);

        .........

        switch (PyUnicode_CHECK_INTERNED(s)) {
        case SSTATE_INTERNED_IMMORTAL:
            Py_SET_REFCNT(s, Py_REFCNT(s) + 1);
            break;
        case SSTATE_INTERNED_MORTAL:
            // Restore the two references (key and value) ignored
            // by PyUnicode_InternInPlace().
            Py_SET_REFCNT(s, Py_REFCNT(s) + 2);
            break;
        case SSTATE_NOT_INTERNED:
            /* fall through */
        default:
            Py_UNREACHABLE();
        }

        // marking the string to be NOT_INTERNED
        _PyUnicode_STATE(s).interned = SSTATE_NOT_INTERNED;
    }

    // decreasing the reference to the initialized and
    // access keys object.
    Py_DECREF(keys);

    // clearing the dictionary
    PyDict_Clear(interned);

    // clearing the object interned
    Py_CLEAR(interned);
}
```

## String Interning in Action

Now that we understand the internals of String Interning and Cleanup, we find out what all Strings are interned in Python. To discover the spots all we do is grep for the function invocation for `PyUnicode_InternInPlace` in the CPython source code and peek at the neighbouring code.


### Variables, Constants and Function Names

CPython performs String Interning on constants such as Function Names, Variable Names, String Literals, etc. Following is the snippet from [codeobject.c](https://github.com/python/cpython/blob/master/Objects/codeobject.c) where the new `PyCode` object is created where we see the interpreter interning all the compile-time constants, names, and literals.

```cpp
...
PyCodeObject *
PyCode_NewWithPosOnlyArgs(int argcount, int posonlyargcount, int kwonlyargcount,
                          int nlocals, int stacksize, int flags,
                          PyObject *code, PyObject *consts, PyObject *names,
                          PyObject *varnames, PyObject *freevars, PyObject *cellvars,
                          PyObject *filename, PyObject *name, int firstlineno,
                          PyObject *linetable)
{

    ........

    if (intern_strings(names) < 0) {
        return NULL;
    }

    if (intern_strings(varnames) < 0) {
        return NULL;
    }

    if (intern_strings(freevars) < 0) {
        return NULL;
    }

    if (intern_strings(cellvars) < 0) {
        return NULL;
    }

    if (intern_string_constants(consts, NULL) < 0) {
        return NULL;
    }

    ........

}
...
```

### Dictionary Keys

CPython performs String Interning on the keys of the dictionary. Upon setting an item in the dictionary, the interpreter performs String Interning on the key. The following code is taken from [dictobject.c](https://github.com/python/cpython/blob/master/Objects/dictobject.c) shows how the interpreter is Interning the Keys of the dictionary while setting an item.

```cpp
int
PyDict_SetItemString(PyObject *v, const char *key, PyObject *item)
{
    PyObject *kv;
    int err;
    kv = PyUnicode_FromString(key);
    if (kv == NULL)
        return -1;

    // Invoking String Interning on the key
    PyUnicode_InternInPlace(&kv);

    err = PyDict_SetItem(v, kv, item);
    Py_DECREF(kv);
    return err;
}
```

### Attributes of any Object

Objects in Python can have attributes that can be set using `setattr` function. It turns out that all the attribute names are interned. Following is the snippet of the function `PyObject_SetAttr` responsible for setting a new attribute to a Python object, defined in the file [object.c](https://github.com/python/cpython/blob/master/Objects/object.c).

```cpp
int
PyObject_SetAttr(PyObject *v, PyObject *name, PyObject *value)
{

    ........

    PyUnicode_InternInPlace(&name);

    ........
}
```

The above snippet shows how a Python interpreter, while setting an attribute to a Python object, also interns the attribute name.

### Explicit Interning

Python allows explicit String Interning through the function `intern` defined in `sys` module. When this function is invoked with any String object, the provided String object is interned. Following is the code snippet from the file [sysmodule.c](https://github.com/python/cpython/blob/master/Python/sysmodule.c) that shows how `sys.intern` function interns the provided String.

```cpp
static PyObject *
sys_intern_impl(PyObject *module, PyObject *s)
{

    ........

    if (PyUnicode_CheckExact(s)) {
        Py_INCREF(s);
        PyUnicode_InternInPlace(&s);
        return s;
    }

    ........
}
```

## Intrinsic details about String Interning

*Only compile-time strings are interned*. Strings that are specified during interpretation or compile-time are interned. Dynamically created strings are not interned.

*Strings having ASCII letters and underscores are interned*. During compile time when general string literals are observed for interning, CPython ensues that the literals that match the regular expression `[a-zA-Z0-9_]*` are interned. This is defined in the function named `all_name_chars` in file [codeobject.c](https://github.com/python/cpython/blob/master/Objects/codeobject.c).

# References

- [String Interning](https://en.wikipedia.org/wiki/String_interning)
- [CPython Optimizations](https://stummjr.org/post/cpython-optimizations/)
- [Python Objects Part III: String Interning](https://medium.com/@bdov_/https-medium-com-bdov-python-objects-part-iii-string-interning-625d3c7319de)
- [The internals of Python string interning](http://guilload.com/python-string-interning/)
