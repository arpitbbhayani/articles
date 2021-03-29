# The Weird Walrus

Python in version 3.8 introduced [Assignment Expressions](https://realpython.com/lessons/assignment-expressions/) which can be used with the help of the Walrus Operator `:=`. This expression does assign and return in the same expression helping in writing a concise code.

Say you are building your own shell in Python. It takes commands and input from the prompt, executes it on your shell, and renders the output. The shell should stop the execution as soon as it receives the `exit` command. This seemingly complicated problem can be built using just 4 lines of Python code.

```python
command = input(">>> ")
while command != "exit":
    os.system(command)
    command = input(">>> ")
```

Although the above code runs perfectly fine, we can see that the `input` is taken twice, once outside the loop and once within the loop. This kind of use case is very common in Python.

Walrus Operator fits perfectly here; now instead of initializing `command` with `input` outside and then checking if `command != 'exit'`, we can merge the two logic in one expression. The 4 lines of code above can be rewritten into the most intuitive 2 lines

```python
while (command := input(">>> ")) != "exit":
    os.system(command)
```

# What's weird with Walrus operator?

Now that we have established how useful the Walrus Operator could be for us, let's dive into the weird stuff. Since the Walrus operator has functioning similar to an assignment operator `=`, we would expect the following code to work fine, but it actually gives an error, not just any but a `SyntaxError`.

```python
>>> a := 10
  File "<stdin>", line 1
    a := 10
      ^
SyntaxError: invalid syntax
```

If you thought, that was weird wait till we wrap the exact same statement with parenthesis and execute it.

```python
>>> (a := 10)
10
```

What! it worked! How? What happened here? Just by wrapping the statement by parenthesis made an invalid Syntax valid? Isn't it weird? This behavior is pointed out in a Github repository called [wtf-python](https://github.com/satwikkansal/wtfpython#-first-things-first-). The theoretical explanation for this behavior is simple; Python disallows non-parenthesized Assignment Expressions but it allows non-parenthesized assignment statements.

In this essay, we dig deep into CPython and find out hows' and the whys'.

# The hows' and the whys'

Few points to note:

- The Walrus Operator or Assignment Expressions are called Named Expressions in CPython.
- The branch of the CPython we are referring to here is for version `3.8`

## The Grammar

If `a := 10` is giving us a Syntax Error then it must be linked to the Grammar specification of the language. The grammar of Python can be found in file [Grammar/Grammar](https://github.com/python/cpython/blob/3.8/Grammar/Grammar). So if we grep `namedexpr` in the Grammar file we get the following rules

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

The above Grammar rules give us a good gist of how Named Expressions are supposed to be used. Here are some observations about it -

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

So when we run `a := 1`, none of the Grammar rules is satisfied and hence this results in a `SyntaxError`.

## What about `if` and `while`?

According to the rule `if_stmt` and `while_stmt` you can have named expressions right after `if` without needing any brackets surrounding it. This means the following statement is valid, but still chose to put parenthesis around `:=`, why?

```python
while command := input(">>> ") != "exit":
```

Answer is simple, [Operator Precedence](https://en.wikipedia.org/wiki/Order_of_operations); because of the configured precedence the above statement sets `command` as `bool` after evaluating `input(">>> ") != "exit"` but we do not want this behaviour. Instead, we want `command` to be set as a command given as an input through `input` call and hence we wrap the expression with parenthesis for specifying explicit precedence.

# Allowing `a := 10`

Till now we saw how doing `a := 10` on a fresh Python prompt gives us a `SyntaxError`, so how about altering the CPython to allow `a := 10`? Sounds fun, isn't it?

## Changing the Grammar

To achieve what we want to we will have to alter the Grammar rules. A good point to note here is that as a standalone statement, `:=` works and behaves very similar to a regular assignment statement having an `=`. So let's first find out, where have we allowed regular assignment statements 

```
stmt: simple_stmt | compound_stmt
simple_stmt: small_stmt (';' small_stmt)* [';'] NEWLINE
small_stmt: (expr_stmt | del_stmt | pass_stmt | flow_stmt |
             import_stmt | global_stmt | nonlocal_stmt | assert_stmt)
expr_stmt: testlist_star_expr (annassign | augassign (yield_expr|testlist) |
                     [('=' (yield_expr|testlist_star_expr))+ [TYPE_COMMENT]] )
```

The regular assignment statements are allowed as per `expr_stmt` rule which is in turn a `small_stmt`, `simple_stmt`, and `stmt`. Rules are self-explanatory and skimming them would help you understand what exactly is happening in there.

In order to mimic the behavior of `:=` to be the same as `=` how about adding a new rule in `expr_stmt` that suggests matching the same pattern as `=`. So we make the following change in `expr_stmt`.

```
expr_stmt: testlist_star_expr (annassign | augassign (yield_expr|testlist) |
                     [('=' (yield_expr|testlist_star_expr))+ [TYPE_COMMENT]] |
                     [(':=' (yield_expr|testlist_star_expr))+ [TYPE_COMMENT]] )
```

When we change anything in the `Grammar` file, we have to regenerate the parser code; and this can be done using the following command

```
$ make regen-grammar
```

Once the above command is successful, we generate a fresh Python binary and see our changes in action.

```
$ make && ./python.exe
```

On the fresh prompt that would have popped up try putting in `a := 10`, once you do this you will find out that this does not give any error and it executes seamlessly and it works just like a normal assignment statement, the behavior that we were seeking.

So with these changes, we have our Python interpreter that supports all the three statements

```python
>>> a = 10
>>> (b := 10)
10
>>> c := 10
```

All of these changes were made on my own [fork of cpython](https://github.com/arpitbbhayani/cpython) and the PR can be found [here](https://github.com/arpitbbhayani/cpython/pull/8).

# References

- [CPython Source Code Guide](https://realpython.com/cpython-source-code-guide/)
- [Exploring CPython’s Internals](https://devguide.python.org/exploring/)
- [wtfpython - Github Repository](https://github.com/satwikkansal/wtfpython)
- [Assignment Expressions: The Walrus Operator](https://realpython.com/lessons/assignment-expressions/)
