Function overloading is the ability to have multiple functions with the same name but with different signatures/implementations. When an overloaded function `fn` is called, the runtime first evaluates the arguments/parameters passed to the function call and judging by this invokes the corresponding implementation.

```cpp
int area(int length, int breadth) {
  return length * breadth;
}

float area(int radius) {
  return 3.14 * radius * radius;
}
```

In above example (written in C++), the function `area` is overloaded with two implementations; one accepts two arguments (both integers) representing the length and the breadth of a rectangle and returns the area; while the other function accepts an integer radius of a circle. When we call the function `area` like `area(7)` it invokes the second function while `area(3, 4)` invokes the first.

### Why no Function Overloading in Python?
Python does not support function overloading. When we define multiple functions with same name, the later one always overrides the prior and thus, in the namespace, there will always be a single entry against each function name. We see what exists in Python namespaces by invoking functions `locals()` and `globals()`, which returns local and global namespace respectively.

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

Calling the function `locals()` after defining a function we see that it returns a dictionary of all variables defined in local namespace. The key of the dictionary is the name of the variable and value is the reference/value of that variable. When the runtime encounters another function with the same name it updates the entry in the local namespace and thus removes the possibility of two functions co-existing. Hence python does not support Function overloading. It was the design decision made while creating language but this does not stop us from implementing it, so let's overload some functions.

# Implementing Function Overloading in Python
We know how Python manages namespaces and if we would want to implement function overloading, we would need to

 - manage the function definitions in a maintained virtual namespace
 - find a way to invoke the correct function as per the arguments passed to it

To keep things simple, we will implement function overloading where for the functions with same name are distinguished by the **number of arguments** it accepts.

## Wrapping the function
We create a class called `Function` that wraps any function and makes it callable through an overridden `__call__` method and also exposes a method called `key` that returns a tuple which makes this function unique in entire codebase.

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

In the snippet above, the `key` function returns a tuple that uniquely identifies the function in the codebase and holds

 - module of the function
 - class to which the function belongs
 - name of the function
 - number of arguments the function accepts

The overridden `__call__` method invokes the wrapped function and returns the computed value (nothing fancy here right now). This makes the instance callable just like the function and it behaves exactly like the wrapped function.

```py
def area(l, b):
  return l * b

>>> func = Function(area)
>>> func.key()
('__main__', <class 'function'>, 'area', 2)
>>> func(3, 4)
12
```

In the example the function `area` is wrapped in `Function` instantiated in `func`. The `key()` returns the tuple whose first element is the module name `__main__`, second is the class `<class 'function'>`, the third is the function name `area` while the fourth is the number of arguments that function `area` accepts which is `2`.

The example also shows how we could just call the instance `func`, just like the usual `area` function, with arguments `3` and `4` and get the response `12`, which is exactly what we'd get is we would have called `area(3, 4)`. This behaviour would come in handy in the later stage when we play with decorators.

## Building the virtual Namespace
Virtual Namespace, we build here, will stores all the functions we gather during definition phase. As there be only one namespace/registry we create a singleton class which holds the functions in a dictionary whose key will not be just a function name but the tuple we get from the `key` function, which contains elements that uniquely identifies function in the entire codebase. Through this we will be able to hold functions in the registry even if they have same name (but different arguments) and thus facilitating function overloading.

```py
class Namespace(object):
  """Namespace is the singleton class that is responsible
  for holding all the functions.
  """
  __instance = None

  def __init__(self):
    if self.__instance is None:
      self.function_map = dict()
      Namespace.__instance = self
    else:
      raise Exception("cannot instantiate a virtual Namespace again")

  @staticmethod
  def get_instance():
    if Namespace.__instance is None:
      Namespace()
    return Namespace.__instance

  def register(self, fn):
    """registers the function in the virtual namespace and returns
    an instance of callable Function that wraps the
    function fn.
    """
    func = Function(fn)
    self.function_map[func.key()] = fn
    return func
```

The `Namespace` has a method `register` that takes function `fn` as argument, creates unique key for it, stores it in the dictionary and returns `fn` wrapped within an instance of `Function`. This means the return value from `register` function is also callable and (till now) its behavior is exactly same as the wrapped function `fn`.

```py
def area(l, b):
  return l * b

>>> namespace = Namespace.get_instance()
>>> func = namespace.register(area)
>>> func(3, 4)
12
```

## Using decorators as a hook
Now that we have defined a virtual namespace with an ability to register a function, we need a hook that gets called during function definition; and here use Python decorators. In Python, a decorator wraps a function and allows us to add new functionality to an existing function without modifying its structure. A decorator accepts the wrapped function `fn` as argument and return another function that gets invoked instead. This function accepts `args` and `kwargs` passed during function invocation and returns the value.

A sample decorator that times an execution of a function is demonstrated below

```py
import time


def my_decorator(fn):
  """my_decorator is a custom decorator that wraps any function
  and prints on stdout the time for execution.
  """
  def wrapper_function(*args, **kwargs):
    start_time = time.time()

    # invoking the wrapped function and getting the return value.
    value = fn(*args, **kwargs)
    print("the function execution took:", time.time() - start_time, "seconds")

    # returning the value got after invoking the wrapped function
    return value

  return wrapper_function


@my_decorator
def area(l, b):
  return l * b


>>> area(3, 4)
the function execution took: 9.5367431640625e-07 seconds
12
```

In the example above we define a decorator named `my_decorator` that wraps function `area` and prints on `stdout` the time it took for the execution.

The decorator function `my_decorator` is called every time (so that it could wrap the store this new function in its namespace) the interpreter encounters a function definition, and it is an ideal hook, for us, to register the function in our virtual namespace. Hence we create our decorator named `overload` which registers the function in virtual namespace and return a callable to be invoked.

```py
def overload(fn):
  """overload is the decorator that wraps the function
  and returns a callable object of type Function.
  """
  return Namespace.get_instance().register(fn)
```

The `overload` decorator returns an instance of `Function`, as returned by `.register()` function of the namespace. Now whenever the function (decorated by `overload`) is called, it invokes the function returned by the `.register()` function - an instance of `Function` and the `__call__` method gets executed with specified `args` and `kwargs` passed during invocation.

## Invoking the right function from namespace

```py
def __call__(self, *args, **kwargs):
  """Overriding the __call__ function which makes the
  instance callable.
  """
  # fetching the function to be invoked from the virtual namespace
  # through the arguments.
  fn = Namespace.get_instance().get(self.fn, *args)
  if not fn:
    raise Exception("no matching function found.")

  # invoking the wrapped function and returning the value.
  return fn(*args, **kwargs)
```

## In action

```py
@overload
def area(l * b):
  return l * b

@overload
def area(r):
  return 3.14 * r ** 2


>>> area(3, 4)
12
>>> area(7)
22
```

# Next steps

 - right now arg count based
 - defined types based
 - annotation based

---

_This article was originally published on my blog [Function Overloading in Python](https://arpitbhayani.me/blogs/function-overloading)._

_If you liked what you read, subscribe to my newsletter and get the post delivered directly to your inbox and give me a shout-out [@arpit_bhayani](https://twitter.com/arpit_bhayani)._

[![Subscribe to Arpit's newsletter](https://user-images.githubusercontent.com/4745789/72035595-56396b00-32be-11ea-8199-121d0808a53a.png)](https://arpit.substack.com)
