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

### Python and Function Overloading
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



Python stores functions in `locals()`. When a function is defined it looks like this

```
LOCALS output
```

If you look closely, locals is a dictionary where function name is key and this restrains us from having multiple functions.

When we define another function with same name, the second one will take place of the first.

# Implementing It

## Rough Idea
The rough idea is to maintain `locals` and anytime

## Decorators

## Registry

## Function

---

_This article was originally published on my blog [Function Overloading in Python](https://arpitbhayani.me/blogs/function-overloading)._

_If you liked what you read, subscribe to my newsletter and get the post delivered directly to your inbox and give me a shout-out [@arpit_bhayani](https://twitter.com/arpit_bhayani)._

[![Subscribe to Arpit's newsletter](https://user-images.githubusercontent.com/4745789/72035595-56396b00-32be-11ea-8199-121d0808a53a.png)](https://arpit.substack.com)
