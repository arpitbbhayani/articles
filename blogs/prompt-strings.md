When Python interactive shell starts, it prints some details about the environment, version, OS and then it prints `>>> ` and we understand that it is now ready to take commands.

```py
Python 2.7.10 (default, Feb 22 2019, 21:55:15)
[GCC 4.2.1 Compatible Apple LLVM 10.0.1 (clang-1001.0.37.14)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>>
```

The `>>>` is called the primary prompt string (PS1) which suggests the user that the interactive shell is now
ready to accept the next command and execute it. Python has 2 prompt strings, one primary and another secondary,
with default values being `>>> ` and `... ` and are called ps1 and ps2.

The secondary interpreter prompt string `... ` is seen when an execution unit (statement) spans multiline, for example: defining a function

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
