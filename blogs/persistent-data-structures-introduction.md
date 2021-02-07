Ordinary data structures are ephemeral implying that any update made to it destroys the old version and all we are left with is the updated latest one. Persistent Data Structures change this notion and allow us to hold multiple versions of a data structure at any given instant of time. This enables us to go back in "time" and access any version that we want.

In this essay, we take a detailed look into the world of Persistent Data Structures and see the basics of its implementation along with where exactly we can find them in action. This essay is meant to act as an exhaustive introduction to the topic and in future essays, we will dive deeper into the specifics and implementation details of each data structure.

This essay is loosely based on the iconic paper published in 1986 titled [Making Data Structures Persistent](https://www.cs.cmu.edu/~sleator/papers/making-data-structures-persistent.pdf) by James R. Driscoll, Neil Sarnak, Daniel D. Sleator, and Robert E. Tarjan.

# Persistence

Persistent Data Structures preserve previous versions of themselves allowing us to revisit and audit any historical version. Depending on the operations allowed on the previous versions, persistence is classified into three categories

### Partially Persistent

Partially Persistent Data Structures allows access to all the historical versions but allows modification to only the newest one. This typically makes historical versions of the data structure immutable (read-only).

![https://user-images.githubusercontent.com/4745789/107117960-e4a66480-68a3-11eb-97a0-c8c412527471.png](https://user-images.githubusercontent.com/4745789/107117960-e4a66480-68a3-11eb-97a0-c8c412527471.png)

### Fully Persistent

Fully Persistent Data Structures allows access and modification to all the historical versions. It does not restrict any modifications whatsoever. This means we can typically revisit any historical version and modify it and thus fork out a new branch.

![https://user-images.githubusercontent.com/4745789/107117958-e112dd80-68a3-11eb-971b-58034e693f44.png](https://user-images.githubusercontent.com/4745789/107117958-e112dd80-68a3-11eb-971b-58034e693f44.png)

### Confluently Persistent

Confluently Persistent Data Structures allow modifications to historical versions while also allowing them to be merged with existing ones to create a new version from the previous two. 

![https://user-images.githubusercontent.com/4745789/107117954-da846600-68a3-11eb-9c34-b9489c170710.png](https://user-images.githubusercontent.com/4745789/107117954-da846600-68a3-11eb-9c34-b9489c170710.png)

# Applications of Persistent Data Structures

Persistent Data Structures find their applications spanning the entire spectrum of Computer Science, including but not limited to - Functional Programming Languages, Computational Geometry, Text Editors, and many more.

## Functional Programming Languages

Functional Programming Languages are ideal candidates for incorporating Persistent Data Structures as they forbid, if not discourage, the mutability of underlying structures. These languages pass around states within functions and expect that they return to a new state, leaving the old one unaltered. Programming languages like Haskell, Clojure, Elm, Javascript, Scala have native Persistent implementations of data structures like Lists, Maps, Sets, and Trees.

## Computational Geometry

One of the fundamental problems in Computational Geometry is the [Point Location Problem](https://en.wikipedia.org/wiki/Point_location) which deals with identifying the region where the query point lies. A simpler version of the problem statement is to find if a point lies within or outside a given polygon. A popular solution to determine a solution to the Point Location problem statement uses [Persistent Red-Black Trees](https://en.wikipedia.org/wiki/Red–black_tree).

## Text and File Editing

The most common operation required by any Text or File editing tool is *Undo and Redo* and having persisted all historical versions through a persistent data structure makes these most frequent operations very efficient and a breeze.

# Implementing Partial Persistence

There are a few generic techniques that help in implementing Partial Persistence. Just to reiterate, partial persistence allows access to all the historical versions but allows modification to only the newest one, to create a newer updated copy of data.

## Copy on Write Semantics

A naive way to implement Partial Persistence is by utilizing the Copy-on-Write semantics and naively creating a deep copy upon every update. This technique is inefficient because upon every writes the entire data structure is deep copied.

There are certain methods built upon certain storage paradigms that copy only what matters making the entire CoW efficient. I have already gone in-depth of [Copy-on-Write semantics](https://arpitbhayani.me/blogs/copy-on-write) and I encourage you to check that out.

## The Fat Node Method

Instead of creating copies of the entire data structure, the Fat Node method suggests that each cell holding the value within the data structure is modified to hold multiple values (one for each version) making it arbitrarily *fat*. Each value node thus holds a value and a version stamp.

```python
class Node:
    def __init__(self, value: object):
        # references to other Nodes creating a Node topology
        # that forms the core of the data structure
        # this could be `next` and `prev` pointers in a linked list
        # or `left`, `right` in case of a binary search tree.
        self.refs: List[] = []

        # holding all the values against the version (key)
        self.values: Dict[int, object] = {}
```

## The Node-Copying Method

The Node-Copying method eliminates all the problems with the Fat Node method. It allows each node to hold only a fixed number of values in it. Upon exhaustion of space, a new copy of Node is created and it holds only the newest values in it. The old node also holds pointers to the newly created node allowing browsing.

Having this structure helps in making update operation slightly efficient by reducing the number of nodes to be copied during writes, considering the in-degrees to each node is bounded.

## Path Copying Method

The path copying method copies all the nodes coming in the path from the root to the node being modified. This way it tries to minimize the copy and promotes reusing some of the unmodified data. This method comes in super handy in Linked Data Structures like Lists and Trees.

![https://user-images.githubusercontent.com/4745789/107144006-33b0d000-695e-11eb-9e13-959eaeba44f4.png](https://user-images.githubusercontent.com/4745789/107144006-33b0d000-695e-11eb-9e13-959eaeba44f4.png)

> Implementation of Full Persistence is a mammoth of a topic on its own and deserves its own essay. Hence skipping it from the scope of this one.

# Reducing the memory footprint

Since persistent data structures thrive on high memory usage, they require some garbage collection system like [Reference Counting](https://en.wikipedia.org/wiki/Reference_counting) or [Mark and Sweep](https://en.wikipedia.org/wiki/Mark_and_sweep). These garbage collection systems free up the memory of historical versions that are not being referenced anymore in the program space.

# References

- [Making Data Structures Persistent](https://www.cs.cmu.edu/~sleator/papers/making-data-structures-persistent.pdf)
- [Persistent data structure - Wikipedia](https://en.wikipedia.org/wiki/Persistent_data_structure)
- [Geometric Data Structures](http://www.sccg.sk/~samuelcik/dgs/geom_structures.pdf)
- [Point Location Problem - Wikipedia](https://en.wikipedia.org/wiki/Point_location)
- [Text Editor: Data Structures - HackerNews](https://news.ycombinator.com/item?id=15381886)
