[Persistent Data Structures](https://arpitbhayani.me/blogs/persistent-data-structures-introduction) preserve previous versions of themselves allowing us to revisit and audit any historical version. While we already did an exhaustive introduction in the [previous essay](https://arpitbhayani.me/blogs/persistent-data-structures-introduction), in this essay, we take a detailed look into how we can implement the ***Fully Persistent*** variant of the most common data structure - ***Arrays***.

The essay is loosely based on the paper titled [Fully Persistent Arrays for Efficient Incremental Updates and Voluminous Reads](https://link.springer.com/chapter/10.1007/3-540-55253-7_7) by Tyng-Ruey Chuang and we implement it using Backer's trick elaborated in the paper [A Persistent Union-Find Data Structure](https://www.lri.fr/~filliatr/ftp/publis/puf-wml07.pdf).

# Fully Persistent Arrays

An array is an abstract data structure consisting of `n` slots to hold a maximum of `n` elements such that each element is identified by at least one index. A typical array allows the following functions - `create(n)`, `update(index, value)` and `get(index)`.

The simplest form of an array, that we all are familiar with, is the Linear Array that is designed to hold elements in consecutive memory locations, leveraging spatial locality for faster and more efficient retrievals and scans. Before we jump into the implementation details of Fully Persistent Arrays, let's reiterate what exactly are Fully Persistent Data Structures.

Persistent Data Structures preserve previous versions of themselves allowing us to revisit and audit any historical version. Fully Persistent Data Structures allows access and modification to all the historical versions as well. It does not restrict any modifications whatsoever. This means we can typically revisit any historical version of the data structure, modify it like we are forking out a new branch.

![https://user-images.githubusercontent.com/4745789/107117958-e112dd80-68a3-11eb-971b-58034e693f44.png](https://user-images.githubusercontent.com/4745789/107117958-e112dd80-68a3-11eb-971b-58034e693f44.png)

Fully Persistent Arrays are arrays that support Full Persistence which means it supports usual array operations while also allowing us to go back in time and make updates to any of the previous versions. We define the following operations on Fully Persistent Arrays -

- `create(n)` - returns an array of size `n` having all the slots uninitialized
- `update(array, index, value)` - returns a new array identical to `array` except for the element at the position `index`. The parent array `array` remains unaffected and is still accessible.
- `get(array, index)` - returns the element present at the index `index` in array `array`

# Implementing Fully Persistent Array

A naive way of implementing these arrays is to do a [Copy-on-Write](https://arpitbhayani.me/blogs/copy-on-write) and keep track of historical versions. This approach very inefficient as it requires `m` times the memory required to hold `n` elements, where `m` is the total number of versions of the array.

![https://user-images.githubusercontent.com/4745789/107803148-3cebd380-6d88-11eb-9889-bb551e83c00a.png](https://user-images.githubusercontent.com/4745789/107803148-3cebd380-6d88-11eb-9889-bb551e83c00a.png)

A better way of implementing these arrays is by using the [Backer's Trick](https://www.lri.fr/~filliatr/ftp/publis/spds-rr.pdf) which enables the required functionality with just one array and a tree of modifications.

# Fully Persistent Arrays using Backer's Trick

A more efficient way of implementing Fully Persistent Arrays is by using a single instance of an in-memory Array and in conjunction use a tree of modifications. Instead of storing all the versions separately, Backer's trick allows us to compute any version of the array by replaying all the changes asked for.

## Tree of modifications

The tree of modifications is an `n`-ary tree that holds all the versions of the array by storing only the modifications made to the elements. Each version is derived from a parent version and the root points to the in-memory *cache* array which holds the initial version of it.

![https://user-images.githubusercontent.com/4745789/107856766-71c35d80-6e50-11eb-9f59-c3744cdc884f.png](https://user-images.githubusercontent.com/4745789/107856766-71c35d80-6e50-11eb-9f59-c3744cdc884f.png)

Each node of the tree holds three fields - `index`, `value`, and a pointer to the `parent`, making this tree pointing upwards towards to root. Thus each node holds the changed `value`, where did the change happen `index` and on which version the change happened `parent`.

Say we changed the element at the index `1` of the array `9, 6, 3, 5, 1`  to `7` we get array `9, 7, 3, 5, 1`. The tree of modifications has 2 nodes one root node `a0` pointing to the initial array, and another node `a1` denoting the updated version.

![https://user-images.githubusercontent.com/4745789/107858298-996af380-6e59-11eb-99dc-7a68ea25f5b4.png](https://user-images.githubusercontent.com/4745789/107858298-996af380-6e59-11eb-99dc-7a68ea25f5b4.png)

The node `a1` has 3 fields, `index` set to `1`, `value` set to `7` and `parent` pointing to `a0`. The node implies that it was derived from `a0` by changing the value of the element at the index `1` to `7`. If we try to branch off `a0` with another change say index `4` set to value `9` we would have 3 nodes in the tree. Thus we see how an update translates into just creating a new node and adding it at the right place in the tree.

Now we see with this design how we implement the three functions of an array `create`, `update`, and `get`.

## Implementing `create`

The `create` function allocates a linear array of size `n` to hold `n` elements. This is a usual array allocation. While doing this we also create the root node of our tree of modifications. The root node, as established earlier, points to the *cache* array.

```python
# The function creates a new persistent array of size `n`
def create(n: int) -> Array:
    # 1. allocate in-memory cache
    # 2. initialize the tree of modifications
    # 3. make the root of the tree point to the cache
    pass
```

The overall complexity of this operation is `O(n)` space and `O(n)` time.

## Implementing `update`

The `update` operation takes in the `index` that needs to be updated, the `value`, and the version of the array on which update is to be made.

```python
# The function updates the element at the index `index` with value
# `value` on array `array` and returns the newly updated array
# keeping the old one accessible.
def update(array: Array, index: int, value: object) -> Array:
    # 1. create a node in the tree and store index, the value in it
    # 2. point this new node to the parent array
    pass
```

To do this efficiently, we create a new node in the tree whose parent is set to the array version on which update is performed, index and value are set what was passed during invocation. Thus we see that the `update` operation takes a constant `O(1)` space and `O(1)` time to create and represent a new version of the array.

With the update operation being made efficient we have to trade-off `get` operation.

## Implementing `get`

The `get` operation takes in the `index` that needs to be fetched and the version of the array from which the element is to be fetched. The `get` operation seeks no extra space but takes time proportional to the distance between the array version and the root. In the worst case, this distance will be as long as the total number of versions of the array.

```python
# The function fetches the element from index `index`
# from the array `array` and returns it.
def get(array: Array, index: int) -> object:
    # 1. Start from the requested array and traverse to the root node.
    # 2. Allocate a new register to store the requested value
    # 3. During traversal, if the node.index == `index` update the
    # register with the value.
    # 4. return the value of the register
    pass
```

The overall complexity of this operation is `O(1)` space and `O(n)` time.

# Optimizing successive reads on the same version

We established that the update operation takes constant time and reads are expensive. If our system is write-heavy, then this is pretty handy but if the system has more reads then operation taking `O(n)` time hampers the overall performance of the system. So as to optimize this use case we take a look at the operation called *Rerooting.*

## Rerooting

The initial array (the first version of the array) has no significance to be the root forever. We can reroot the entire tree such that any child node could become the root and the value it points to - *cache* - represents the true copy of the array. Rerooting is a sequence of rotations to make the desired array version the root.

The algorithm for rerooting is a classic Backtracking algorithm that requires updates in all the nodes coming in the path from the old node to the new node.

![https://user-images.githubusercontent.com/4745789/107935855-ee1c8480-6fa7-11eb-9870-2ae90d6460a9.png](https://user-images.githubusercontent.com/4745789/107935855-ee1c8480-6fa7-11eb-9870-2ae90d6460a9.png)

The rerooting operation takes time proportional to the distance between the old and new root ~ `O(n)`. Since the successive reads are happening on the same version the `get` operation becomes `O(1)` as well. Thus depending on the kind of usage of the system we can add rerooting step in either `get` or `update` operation.

# References

- [Persistent Arrays - Wikipedia](https://en.wikipedia.org/wiki/Persistent_array)
- [Semi-Persistent Data Structures](https://www.lri.fr/~filliatr/ftp/publis/spds-rr.pdf)
- [Fully Persistent Arrays for Efficient Incremental Updates and Voluminous Reads](https://link.springer.com/chapter/10.1007/3-540-55253-7_7)
