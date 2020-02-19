When Python interactive shell starts, it prompts something like this

```
Python 2.7.10 (default, Feb 22 2019, 21:55:15)
[GCC 4.2.1 Compatible Apple LLVM 10.0.1 (clang-1001.0.37.14)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>>
```

The `>>>` is called prompt string (PS) which suggests user that prompt is now
ready accept next command/statement/code.

Python has 2 prompt strings `ps1` and `ps2`.

`ps1` is the promary interpreter prompt string, shown above
`ps2` is the secondary interpreter prompt string that suggests statement entered is in complete (because multiline)

The default value os `ps2` is `... ` which you could see when you define function

```
>>> def foo(a, b):
...     return a + b
...
>>>
```

# Changing the prompt string
If you bind either attribute to a non-string object, Python prompts by calling str( ) on the object each time a prompt is output. This feature lets you create dynamic prompting by coding a class that defines __str__ and assigning an instance of that class to sys.ps1 and/or sys.ps2.

# PYTHONSTARTUP
When we want to do this everytime the interactive shell starts i.e. on startup Pyython provides an environment variable named `PYTHONSTARTUP` which accepts any readble Python file and executes it when shell starts.
