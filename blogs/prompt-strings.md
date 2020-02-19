When Python interactive shell starts, it prints out few things

```py
Python 2.7.10 (default, Feb 22 2019, 21:55:15)
[GCC 4.2.1 Compatible Apple LLVM 10.0.1 (clang-1001.0.37.14)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>>
```

The `>>>` is called prompt string (PS) which suggests the user that shell (prompt) is now
ready accept the next command or statement. Python has 2 prompt strings, a primary and a secondary
with default values being `>>> ` and `... ` and are called `ps1` and `ps2`.

 - `ps1` is the primary interpreter prompt string, shown above
 - `ps2` is the secondary interpreter prompt string that is usually shown when statements span multiline

We usually see secondary prompt while defining a function

```py
>>> def foo(a, b):
...     return a + b
...
>>>
```

# Changing the prompt string
If you bind either attribute to a non-string object, Python prompts by calling str( ) on the object each time a prompt is output. This feature lets you create dynamic prompting by coding a class that defines __str__ and assigning an instance of that class to sys.ps1 and/or sys.ps2.

# PYTHONSTARTUP
When we want to do this everytime the interactive shell starts i.e. on startup Pyython provides an environment variable named `PYTHONSTARTUP` which accepts any readble Python file and executes it when shell starts.
