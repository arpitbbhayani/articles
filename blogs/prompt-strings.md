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

# Personalizing the prompt strings
The prompt strings are defined in the [sys](https://docs.python.org/3/library/sys.html) module as [ps1](https://docs.python.org/3/library/sys.html#sys.ps1) and [ps2](https://docs.python.org/3/library/sys.html#sys.ps2). You can see the values set

```py
>>> import sys
>>> sys.ps1
'>>> '
>>> sys.ps2
'... '
```

To render the prompt string Python prints the value given in `sys.ps1` and `sys.ps2` which means changing value of these variables should change the prompt string right away.

```py
>>> import sys
>>> sys.ps1 = '::: '
:::
```

From the example above we see that changing the value of `sys.ps1` to `::: ` changes the prompt to `::: `.

Let's be creative with this and add some colors. We could use [bash color format](https://misc.flogisoft.com/bash/tip_colors_and_formatting) to color the prompt strings.

```py
import sys
sys.ps1 = "\033[1;33m>>>\033[0m "
sys.ps2 = "\033[1;34m...\033[0m "
```

The code snippet above makes your primary prompt string yellow and secondary prompt string blue. Here's how it looks

![Python colored prompt](https://user-images.githubusercontent.com/4745789/74809433-2a74c080-5313-11ea-9cc5-640c68521c8a.png)

### Dynamic prompt strings

The [documentation](https://docs.python.org/3/library/sys.html#sys.ps2) states that if we assign a non-string object to `ps1` or `ps2` then Python prompts by calling `str()` on the object every time a prompt is shown. This means we could define a class with `__str__` and set an instance of it to `sys.ps1` and we could implement all sorts of stateful functionalities.

We could implement [IPython](https://ipython.org/) like prompt through code below

```py
# -*- coding: utf-8 -*-
import sys

class IPythonPromptPS1(object):
  def __init__(self):
    self.line = 0

  def __str__(self):
    self.line += 1
    return "\033[92mIn [%d]:\033[0m " % (self.line)

sys.ps1 = IPythonPromptPS1()
sys.ps2 = "    \033[91m...\033[0m "
```

The above code snippet makes prompt look like this

![ipython prompt](https://user-images.githubusercontent.com/4745789/74816659-92ca9e80-5321-11ea-84be-5eccd9497438.png)

# Setting new prompt strings every time the shell starts
When we want to do this everytime the interactive shell starts i.e. on startup Pyython provides an environment variable named `PYTHONSTARTUP` which accepts any readble Python file and executes it when shell starts.
