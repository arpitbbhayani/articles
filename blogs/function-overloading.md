Function overloading is the ability to create multiple functions with the same name but with different signatures. Thus depending of the arguments/parameters through which a function call will dictate which implementation is executed.

### Python and Function Overloading
Python does not have function overloading. When we define two functions with same name, the second implementation will override the first one.

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
