# The Weird Walrus

Python in version 3.8 introduced Assignment Expressions and to use it we have used the Walrus Operator `:=`. The specialty of this expression is that you assign and return the value in the same expression helping you write concise code.

Let's take an example: Say you are building a `bash` kind of shell in Python. It takes in input `shell` commands and you execute them. Your shell stops running upon receiving the command `exit`. A super simple Python code that does this is:

```python
command = input(">>> ")
while command != "exit":
    os.system(command)
    command = input(">>> ")
```

Although the above code runs perfectly fine, we can see that the `input` is taken twice, once outside the loop and once within the loop. This kind of use case is very common in Python.

Walrus Operator fits this use case perfectly well. Instead of initializing command with `input` outside and then checking if `command != 'exit'`, we can merge the two logic in one expression. The 4 lines of code above can be rewritten into the most intuitive 2 lines

```python
while (command := input(">>> ")) != "exit":
    os.system(command)
```

# What's weird with Walrus operator?

Since the Walrus operator has functioning similar to an assignment operator, we would expect the following code to work fine, but it actually gives an error, not just any but rather Syntax Error.

```python
>>> a := 10
  File "<stdin>", line 1
    a := 10
      ^
SyntaxError: invalid syntax
```

But when we wrap the very statement with parenthesis, it works and does what we expect it to do.

```python
>>> (a := 10)
10
```

So, just by wrapping the statement by parenthesis made an Invalid Syntax valid? Isn't it weird? This behavior is pointed out in a Github repository called [wtf-python](https://github.com/satwikkansal/wtfpython#-first-things-first-) and today we go through the CPython code and find out why it behaves like this.

# Let's find out why

Few points to note:

- The Walrus Operator or Assignment expressions are called Named expressions in CPython.
- The branch of the CPython we are referring to here is for version `3.8`

## The Grammar

If `a := 10` is giving us a Syntax Error then it must be linked to the Grammar specification of the language. The grammar of Python can be found in file [Grammar/Grammar](https://github.com/python/cpython/blob/3.8/Grammar/Grammar) and token definitions can be found in [Grammar/Tokens](https://github.com/python/cpython/blob/3.8/Grammar/Tokens). If we grep `namedexpr` in the Grammar file we get the following rules

```
namedexpr_test: test [':=' test]

atom: ('(' [yield_expr|testlist_comp] ')' |
       '[' [testlist_comp] ']' |
       '{' [dictorsetmaker] '}' |
       NAME | NUMBER | STRING+ | '...' | 'None' | 'True' | 'False')

testlist_comp: (namedexpr_test|star_expr) ( comp_for | (',' (namedexpr_test|star_expr))* [','] )

if_stmt: 'if' namedexpr_test ':' suite ('elif' namedexpr_test ':' suite)* ['else' ':' suite]

while_stmt: 'while' namedexpr_test ':' suite ['else' ':' suite]
```

The above Grammar rules give us a good gist of how Named Expressions are supposed to be used. Here are some pointers

- can be used in `while` statements
- can be used along with `if` statements
- named expressions are part of a rule called `testlist_comp`, which seems related to list comprehensions

We can see that the `atom` rules put in a hard check that `testlist_comp` should be either surrounded by `()` or `[]` and since `testlist_comp` can have `namedexpr_test` this puts in the check that Named Expressions should be surrounded by `()` or `[]`. 

```
>>> (a := 1)
1
>>> [a := 1]
[1]
```

## What about `if` and `while`?

According to the rule `if_stmt` and `while_stmt` you can have named expressions right after `if` without needing any brackets surrounding it. This means the following statements are valid, but still chose to put parenthesis around `:=`, but why?

```python
while command := input(">>> ") != "exit":
```

Answer is simple, [Operator Precedence](https://en.wikipedia.org/wiki/Order_of_operations); because of configured precedence the above statement sets `command` as `bool` after evaluating `input(">>> ") != "exit"` but we do not want this behaviour. Instead, we want `command` to be set as a command given as an input through `input` and hence we wrap the expression with parenthesis.

# Allowing `a := 10`

Above we saw how doing `a := 10` on a fresh Python prompt gives us a Syntax Error, so what if we alter the CPython and allow `a := 10` to work just fine.

Note: This is all about having fun with the language and hoping to understand the internals better.

## Changing the Grammar

Now that we decided to allow `:=` as a standalone statement we will have to change the Grammar we visited earlier. As a standalone statement `:=` works the same as regular assignment expressions `=`, so let's find where it is defined. 

```
stmt: simple_stmt | compound_stmt
simple_stmt: small_stmt (';' small_stmt)* [';'] NEWLINE
small_stmt: (expr_stmt | del_stmt | pass_stmt | flow_stmt |
             import_stmt | global_stmt | nonlocal_stmt | assert_stmt)
expr_stmt: testlist_star_expr (annassign | augassign (yield_expr|testlist) |
                     [('=' (yield_expr|testlist_star_expr))+ [TYPE_COMMENT]] )
```

The regular assignment statements are allowed as per `expr_stmt` rule which is in turn `small_stmt`, `simple_stmt`, and `stmt`. So let's alter this rule and also allow `:=` operator. By making the change our `expr_stmt` becomes

```
expr_stmt: testlist_star_expr (annassign | augassign (yield_expr|testlist) |
                     [('=' (yield_expr|testlist_star_expr))+ [TYPE_COMMENT]] |
                     [(':=' (yield_expr|testlist_star_expr))+ [TYPE_COMMENT]] )
```

Once we have changed the `Grammar` file we have to regenerate the parser file and for that execute the following command

```
$ make regen-grammar
```

Now we are ready to build a new Python binary and see if our changes work fine or now. For this, we run

```
$ make
```

Once the `make` ends with no errors we open the shell using `./python.exe` and fire the statement

 `a := 10` and we see that this time it did not give any Syntax Error rather is executed just like a normal assignment statement, which is exactly what we wanted. So with these changes, our Python now supports all the three statements mentioned below

```python
>>> a = 10
>>> (b := 10)
10
>>> c := 10
```

The changes can be found as a [PR](https://github.com/arpitbbhayani/cpython/pull/8) on my forked version of CPython.

# References

- [CPython Source Code Guide](https://realpython.com/cpython-source-code-guide/)
- [Exploring CPython’s Internals](https://devguide.python.org/exploring/)
- [wtfpython - Github Repository](https://github.com/satwikkansal/wtfpython)
- [Assignment Expressions: The Walrus Operator](https://realpython.com/lessons/assignment-expressions/)
