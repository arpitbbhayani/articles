Function overloading is the ability to have multiple functions with the same name but with different signatures. When an overloaded function `fn` is called, the runtime first sees the arguments/parameters passed to the function call and judging by this executes the corresponding implementation.

```cpp
int area(int length, int breadth) {
  return length * breadth;
}

float area(int radius) {
  return 3.14 * radius * radius;
}
```

In above example, the function `area` is overloaded with two implementations; one accepts two arguments (both integers) representing the length and the breadth of a rectangle and returns the area; while the other `area` function accepts an integer radius of a circle and returns the area.

When some code calls the function `area` like `area(7)`, the runtime checks the number of arguments and types associated with each, and decides to call the second `area` function.

### Why no Function Overloading in Python?
Python does not have function overloading. In Python, if we define two functions with same name, the second definition override the first. Python manages local and global namespaces and we could access it through `locals()` and `globals()` function calls.

```py
def area(radius):
  return 3.14 * radius ** 2

>>> locals()
{
  ...
  'area': <function area at 0x10476a440>,
  ...
}
```

Calling the `locals()` function after defining a function we see that it returns a dictionary of all variables defined in local namespace. The key of the dictionary is the name of the variable and value is the reference or value of that variable. When the runtime encounters another function with the same name it updates the entry in the local namespace and thus removes the possibility of two functions co-existing.

Challenge accepted!

# Implementing Function Overloading in Python

We know why Python does not support Function Overloading and how it manages namespaces we could come up with an approach that helps us overload Python functions by

 - managing the function definitions in a maintained registry (acting as virtual namespace)
 - invoking the correct function as per the arguments passed to it

### The scope
In this article we will implement function overloading in Python; where for the functions with same name the distinguishing criteria will be the **number of arguments** it accepts.

## Wrapping the function
We create a class called `Function` that wraps any python function and makes it callable through `__call__` and exposes a methods `key` that returns a key that makes this function unique.

```py
from inspect import getfullargspec

class Function(object):
  """Function is a wrap over standard python function.
  """
  def __init__(self, fn):
    self.fn = fn

  def __call__(self, *args, **kwargs):
    """when invoked like a function it internally invokes
    the wrapped function and returns the returned value.
    """
    return self.fn(*args, **kwargs)

  def key(self, args=None):
    """Returns the key that will uniquely identifies
    a function (even when it is overloaded).
    """
    # if args not specified, extract the arguments from the
    # function definition
    if args is None:
      args = getfullargspec(self.fn).args

    return tuple([
      self.fn.__module__,
      self.fn.__class__,
      self.fn.__name__,
      len(args or []),
    ])
```

In the snippet above, the `__call__` invokes the wrapped function and returns the values (nothing fancy here right now). The `key` function returns a tuple which has module, class, function name and the number of arguments it accepts. This tuple can unique identify the wrapped function in the codebase.

```py
def area(l, b):
  return l * b

>>> func = Function(area)
>>> func.key()
('__main__', <class 'function'>, 'area', 2)
>>> func(3, 4)
12
```

In the example above we could see the tuple that is returned from the `key` function for the wrapped function `area`. The first element of tuple is the module name `__main__`, second is the class `<class 'function'>`, the third is the function name `area` while the fourth is the number of arguments that function `area` accepts which is `2`. The example also shows how we could just invoke the instance `func`, just like usual `area` function with arguments `3` and `4` and get the expected response `12` in return.

## Building the registry
Registry, we build here, will stores functions in a "unique" way in a virtual namespace, registry. Hence be build a singleton class (a class that is instantiated exactly once) which will hold our function dictionary. This dictionary should not use function name as key; instead should create a composite key using function name and number of arguments as unique key. We define `Registry` as follow

```py
class Registry(object):
  """Registry is the singleton class that is responsible
  for holding all the functions.
  """
  __instance = None

  def __init__(self):
    if self.__instance is None:
      self.function_map = dict()
      Registry.__instance = self
    else:
      raise Exception("cannot instantiate Registry again")

  @staticmethod
  def get_instance():
    if Registry.__instance is None:
      Registry()
    return Registry.__instance

  def register(self, fn):
    """registers the function in the registry and returns
    an instance of callable Function that wraps the
    function fn.
    """
    func = Function(fn)
    specs = getfullargspec(fn)
    self.function_map[func.key(args=specs.args)] = fn
    return func
```

The `Registry` class will have function `register` that takes function as argument and using function `inspect.getfullargspec` extracts the arguments the function would take and uses it to define unique key for that function.


## Using decorators as a hook
When a function is decorated with a decorator, the decorator function gets executed during function definition; which means this


Decorators execute on every function definition and we use them to persist function definitions in our registry.

## Invoking the correct function from Registry

# Next steps

 - right now arg count based
 - defined types based
 - annotation based

---

_This article was originally published on my blog [Function Overloading in Python](https://arpitbhayani.me/blogs/function-overloading)._

_If you liked what you read, subscribe to my newsletter and get the post delivered directly to your inbox and give me a shout-out [@arpit_bhayani](https://twitter.com/arpit_bhayani)._

[![Subscribe to Arpit's newsletter](https://user-images.githubusercontent.com/4745789/72035595-56396b00-32be-11ea-8199-121d0808a53a.png)](https://arpit.substack.com)
