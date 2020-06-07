C language does not support inheritance however it does support Structure Compositions which can be tweaked to serve use-cases requiring parent-child relationships. In this article, we find out how Structure Compositions help us emulate inheritance in C and keep our code extensible. We will also find how it powers two of the most important things to have ever been invented in the field of computer science.

# What is structure composition?

Structure Composition is when we put one structure within another, not through its pointer but as a native member - something like this

```cpp
// this structure defines a node of a linked list and
// it only holds the pointers to the next and the previous
// nodes in the linked list.
struct list_head {
	struct list_head *next; // pointer to the node next to the current one
	struct list_head *prev; // pointer to the node previous to the current one
};

// list_int holds an list_head and an integer data member
struct list_int {
	struct list_head list;  // common next and prev pointers
	int value;              // specific member as per implementation
};

// list_int holds an list_head and an char * data member
struct list_str {
	struct list_head list;  // common next and prev pointers
	char * str;             // specific member as per implementation
};
```

In the example above, we define a node of a linked list using structure composition. Usually, a linked list node has 3 members - two pointers to adjacent nodes (next and previous) and a third one could either be the data or a pointer to it.  The defining factor of a linked list is the two pointers that logically form a chain of nodes. To keep things abstract we create a struct named `list_head` which holds these two pointers  `next` and `prev` and omits the specifics i.e. data.

Using `list_head` structure, if we were to define a node of a linked list holding an integer value we could create another struct, named `list_int` that holds a member of type `list_head` and an integer value `value`. The next and previous pointers are brought into this struct through `list_head list` and could be referred to as `list.next` and `list.prev`.

> There is a very genuine reason for picking such weird names for a linked list node and members of structures; the reason to do so will be cleared in the later sections of this essay.

Because of the above structure definition, building a linked list node holding of any type becomes a breeze. For example, a node holding string could be quickly defined as a struct `list_str` having `list_head` and a `char *`. This ability to extend `list_head` and build a node holding data of any type and any specifics make low-level code simple, uniform, and extensible.

## Memory Representation of `list_int`

Structures in C are not padded and they do not even hold any meta information, not even for the member names; hence during allocation, they are allocated the space just enough to hold the actual data.

![https://user-images.githubusercontent.com/4745789/83953834-694a6a00-a861-11ea-8ff7-fa69af6af7d6.png](https://user-images.githubusercontent.com/4745789/83953834-694a6a00-a861-11ea-8ff7-fa69af6af7d6.png)

In the illustration above we see how members of `list_int` are mapped on the allocated space - required by its individual members. It is allocated a contiguous space of 12 bytes - 4 bytes for each of the two pointers and another 4 bytes for the integer value. The contiguity of space allocation and order of members during allocation could be verified by printing out their addresses as shown below.

```cpp
void print_addrs() {
    // creating a node of the list_int holding value 41434
    struct list_int *ll = new_list_int(41434);

    // printing the address of individual members
    printf("%p: head\n",             head);
    printf("%p: head->list.next\n",  &((head->list).next));
    printf("%p: head->list.prev\n",  &((head->list).prev));
    printf("%p: head->value\n",      &(head->value));
}

~ $ make && ./a.out
0x4058f0: head
0x4058f0: head->list.next
0x4058f4: head->list.prev
0x4058f8: head->value
```

We clearly see all the 3 members, occupying 12 bytes contiguous memory segments in order of their definition within the struct.

> The above code was executed on a machine where the size of integer and pointers were 4 bytes each. The results might differ depending on the machine and CPU architecture.

## Casting pointers pointing to struct

In C language, when a pointer to a struct is cast to a pointer to another struct, the engine maps the individual members of a target struct type, depending on their order and offsets, on to the slice of memory of the source struct instance.

When we cast `list_int *` into `list_head *`, the engine maps the space required by target type i.e. `list_head` on space occupied by `list_int`. This means it maps the 8 bytes required by `list_head` on the first 8 bytes occupied by `list_int` instance. Going by the memory representation discussed above, we find that the first 8 bytes of `list_int` are in fact `list_head`, and hence casting `list_int *` to `list_head *` is effectively just referencing the `list_head` member of `list_int` through a new variable.

![https://user-images.githubusercontent.com/4745789/83943610-2e254800-a81b-11ea-8b25-056e1b1df85e.png](https://user-images.githubusercontent.com/4745789/83943610-2e254800-a81b-11ea-8b25-056e1b1df85e.png)

This effectively builds a parent-child relationship between the two structs where we can safely typecast a child `list_int` to its parent `list_head`.

> It is important to note here that the parent-child relationship is established only because the first member of `list_int` is of type `list_head`. it would not have worked if we change the order of members in `list_int`.

# How does this drive inheritance?

As established above, by putting one struct within another as its first element we are effectively creating a parent-child relationship between the two. Since this gives us an ability to safely typecast child to its parent we can define functions that accept a pointer to parent struct as an argument and perform operations that do not really require to deal with specifics. This allows us to **NOT** rewrite the functional logic for every child extensions and thus avoid redundant code.

From the context we have set up, say we want to write a function that adds a node between the two in a linked list. The core logic to perform this operation does not really need to deal with any specifics all it takes is a few pointer manipulations of `next` and `prev`. Hence, we could just define the function accepting arguments of type `list_head *`  and write the function as

```cpp
/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_add(struct list_head *new,
                       struct list_head *prev,
                       struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
```

Since we can safely typecase `list_int *` and `list_str *` to `list_head *` we can pass any of the specific implementations the function `__list_add` and it would still add the node between the other two seamlessly.

Since the core operations on linked lists only require pointer manipulations, we can define these operations as functions accepting `list_head *` instead of specific types like `list_int *`.  Thus we need not write similar functions for specifics. A function to delete a node could be written as

```cpp
/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}
```

Other linked list utilities like *adding a node to tail*, *swapping nodes*, *splicing the list*, *rotating the list*, etc only require manipulations of `next` and `prev` pointers. Hence they could also be written in a very similar way i.e accepting `list_head *` and thus eliminating the need to reimplement function logic for every single child implementation.

This behavior is very similar to how inheritance in modern OOP languages, like Python and Java, work where child is allowed to invoke any parent function.

# Who uses structure compositions?

There are a ton of practical usage of using Structure Compositions but the most famous ones are

## Linux Kernel

In order to keep things abstract and extensible, Linux Kernel uses Structure Composition at several places. One of the most important places where it uses composition is for managing and maintaining Linked Lists, exactly how we saw things above. The struct definitions and code snippets are taken as-is from the [Kernel's source code](https://elixir.bootlin.com/linux/latest/source/include/linux/list.h), and hence the structure and variable names look different than usual.

## Python Type and Object Hierarchy

Python, one of the most important languages in today's world, uses Structure Composition to build Type Hierarchy. Python defines a root structure called `PyObject` which holds reference count, defining the number of places from which the object is referenced - and object type - determining the type of the object i.e. `int`, `str`, `list`, `dict`, etc.

```cpp
typedef struct _object {
    Py_ssize_t     ob_refcnt;  // holds reference count of the object
    PyTypeObject   *ob_type;   // holds the type of the object
} PyObject;
```

Since Python wants these fields to be present in every single object that is created during runtime, it uses structure composition to ensure that objects like integers, floats, string, etc put `PyObject` as their first element and thus establishing a parent-child relationship. A Float object in Python is defined as

```cpp
#define PyObject_HEAD                   PyObject ob_base;

typedef struct {
    PyObject_HEAD
    double ob_fval;    // holds the actual float value
} PyFloatObject;
```

Now writing utility functions that increments and decrements references count on every access of any object could be written as just a single function accepting `PyObject *` as shown below

```cpp
static inline void _Py_INCREF(PyObject *op) {
    op->ob_refcnt++;
}
```

Thus we eradicate a need of rewriting `INCREF` for every single object type and just write it once for `PyObject` and it will work for every single Python object type that is extended through `PyObject`.

# References

- [LinkedLists in Linux Source Code](https://elixir.bootlin.com/linux/latest/source/include/linux/list.h)
- [PyObject - Python Internals Documentation](https://docs.python.org/3/c-api/structures.html#c.PyObject)
- [PyFloatObject - Python Internals Documentation](https://docs.python.org/3/c-api/float.html)
