The `>>> ` we see when the Python interactive shell starts is called the Prompt String. Usually the prompt string suggests us that the interactive shell is now ready to take new commands.

```py
Python 2.7.10 (default, Feb 22 2019, 21:55:15)
[GCC 4.2.1 Compatible Apple LLVM 10.0.1 (clang-1001.0.37.14)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>>
```

Python has 2 prompt strings, one primary `>>>` and one secondary `...` which we usually see when an execution unit (statement) spans multiline, for example: while defining a function

```py
>>> def foo(a, b):
...     return a + b
...
>>>
```

# Personalizing the prompt strings
The prompt strings are defined in the [sys](https://docs.python.org/3/library/sys.html) module as [ps1](https://docs.python.org/3/library/sys.html#sys.ps1) and [ps2](https://docs.python.org/3/library/sys.html#sys.ps2) and just like any other attribute we can change the values of `sys.ps1` and `sys.ps2` and the changes take effect immediately and as a result the prompt we see in the shell changes to the new value.

```py
>>> import sys
>>> sys.ps1 = '::: '
:::
```

From the example above we see that changing the value of `sys.ps1` to `::: ` changes the prompt to `::: `.

As the interactive shell runs in a terminal, we can color and format it using [bash color format](https://misc.flogisoft.com/bash/tip_colors_and_formatting) as shown below

```py
import sys
sys.ps1 = "\033[1;33m>>>\033[0m "
sys.ps2 = "\033[1;34m...\033[0m "
```

The code snippet above makes our primary prompt string yellow and secondary prompt string blue. Here's how it looks

![Python colored prompt](https://user-images.githubusercontent.com/4745789/74897098-03be9480-53bc-11ea-8395-7b3bbb1814dd.png)

## Dynamic prompt strings

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

![ipython prompt](https://user-images.githubusercontent.com/4745789/74897125-18029180-53bc-11ea-86e6-9d0ca6753fb9.png)

# Setting new prompt strings every time the shell starts
It will be pretty annoying if we would have to manually copy-paste and run the snippet of code, every time we start our Python shell, yes you guessed it - we automate it. Python uses an environment variable [PYTHONSTARTUP](https://docs.python.org/3/using/cmdline.html#envvar-PYTHONSTARTUP) which should be the path of a readable file and the file is executed before the first prompt is displayed in interactive mode.

So we dump the code snippet in a file, say `myprompt.py` and export `PYTHONSTARTUP` as

```sh
export PYTHONSTARTUP="~/myprompt.py"
```

Now every time, you start your Python interactive shell, it will execute the file `myprompt.py` and set the prompt strings.

# Taking it to the next level
Combining everything mentioned above a utility is created called [py-prompts](https://github.com/arpitbbhayani/py-prompts) which holds few themes and makes the entire process of setting a theme seamless. Here is a glimpse of the themes that the package holds.

![Pretty Python Prompts GIF](https://user-images.githubusercontent.com/4745789/74897216-539d5b80-53bc-11ea-8cdd-91177b6553b5.gif)

If you want to create your own theme and add it to [py-prompts](https://github.com/arpitbbhayani/py-prompts), then create the python file (that updates `sys.ps1` and/or `sys.ps2`) in [themes](https://github.com/arpitbbhayani/py-prompts/tree/master/themes) folder.

# Conclusion
I hope you found this piece interesting. Python being an exhaustively extensible language made it super-easy for us to change the prompt strings and be creative with it. If you have a theme idea or have already personalized your prompt, share it with me [@arpit_bhayani](https://twitter.com/arpit_bhayani), I will be thrilled to learn more about it.
