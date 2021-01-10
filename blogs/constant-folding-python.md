Every programming language aims to be performant in its niche and achieving superior performance requires a lot of compiler level optimizations. One famous optimization technique is [Constant Folding](https://en.wikipedia.org/wiki/Constant_folding) where during compile time the engine tries to recognize constant expressions, evaluate them, and replaces the expression with this newly evaluated value, making the runtime leaner.

In this essay, we dive deep and find what exactly is Constant Folding, understand the scope of it in the world of Python and finally go through Python's source code - [CPython](https://github.com/python/cpython/) - and find out how elegantly Python actually implements it.

# Constant Folding

In [Constant Folding](https://en.wikipedia.org/wiki/Constant_folding), the engine finds and evaluates constant expressions at compile time rather than computing them at runtime, making the runtime leaner and faster.

```python
day_sec = 24 * 60 * 60
```

When the compiler encounters a constant expression, like above, it evaluates the expression and replaces it with the evaluated value. The expression is usually replaced by the evaluated value in the [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree), but the implementation is totally up to the language. Hence the above expression is effectively executed as

```python
day_sec = 86400
```

# Constant Folding in Python

In Python, we could use the [Disassembler module](https://docs.python.org/3/library/dis.html#module-dis) to get the CPython bytecode giving us a good peek at how things will be executed. When we disassemble the above constant expression using the `dis` module, we get the following bytecode

```python
>>> import dis
>>> dis.dis("day_sec = 24 * 60 * 60")

        0 LOAD_CONST               0 (86400)
        2 STORE_NAME               0 (day_sec)
        4 LOAD_CONST               1 (None)
        6 RETURN_VALUE
```

We see that the bytecode, instead of having two binary multiply operations followed by one `LOAD_CONST`, is having just one `LOAD_CONST` with the already evaluated value of `86400`. This indicates that the CPython interpreter during parsing and building of Abstract Syntax Tree folded the constant expression, `24 * 60 * 60` and replaced it with the evaluated value `86400`.

### Scope of Constant Folding

Python tries to fold every single constant expression present but there are some cases where even though the expression is constant, but Python chooses not to fold it. For example, Python does not fold `x = 4 ** 64` while it does fold `x = 2 ** 64`. 

Apart from the arithmetic expressions, Python also folds expressions involving Strings and Tuples, where constant string expressions till the length `4096` are folded.

```python
>>> a = "-" * 4096   # folded
>>> a = "-" * 4097   # not folded
>>> a = "--" * 4096  # not folded
```

# Internals of Constant Folding

Now we shift our focus to the internals and find exactly where and how CPython implements Constant Folding. All AST optimizations, including Constant Folding, can be found in file [ast_opt.c](https://github.com/python/cpython/blob/master/Python/ast_opt.c). The base function starting it all is `astfold_expr` which folds any and every expression that Python source has. The function recursively goes through the AST and tries to fold every constant expression, as seen in the snippet below.

![https://user-images.githubusercontent.com/4745789/103898628-38922200-511b-11eb-965f-fb4d46d3c45c.png](https://user-images.githubusercontent.com/4745789/103898628-38922200-511b-11eb-965f-fb4d46d3c45c.png)

The `astfold_expr` before folding the expression at hand, tries to fold its child expressions (operands) and then delegates the folding to the corresponding specific expression folding function. The operation-specific folding function evaluates the expression and returns the evaluated constant value, which is then put into the AST.

For example, whenever `astfold_expr` encounters a binary operation, it recursively folds the two child operands (expressions) before evaluating the expression at hand using `fold_binop`. The function `fold_binop` returns the evaluated constant value as seen in the snippet below.

![https://user-images.githubusercontent.com/4745789/103898745-670ffd00-511b-11eb-88a9-f741157473b3.png](https://user-images.githubusercontent.com/4745789/103898745-670ffd00-511b-11eb-88a9-f741157473b3.png)

`fold_binop` function folds the binary operation by checking the kind of operator at hand and then invoking the corresponding evaluation function on them. For example, if the operation at hand is an addition then, to evaluate the final value, it invokes `PyNumber_Add` on both its left and right operands.

### What makes this elegant?

Instead of writing special logic to handle certain patterns or types to fold constant expressions efficiently, CPython invokes the same general code. For example, it invokes the same usual `PyNumber_Add` function while folding that it does to perform the usual addition operation.

CPython has thus eradicated the need to write special functions to handle constant folding by making sure its code and evaluation process is structured in such a way that the general-purpose code itself can handle the evaluation of constant expressions.

# References

- [Constant Folding](https://en.wikipedia.org/wiki/Constant_folding)
- [CPython Optimizations](https://stummjr.org/post/cpython-optimizations/)
- [Python dis module and constant folding](https://yasoob.me/2019/02/26/python-dis-module-and-constant-folding/)
- [The simple way CPython does constant folding](https://utcc.utoronto.ca/~cks/space/blog/python/CPythonConstantFolding)
- [A constant folding optimization pass for the AST](https://bugs.python.org/issue1346238)
