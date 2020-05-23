Consistent hashing 

Three major examples of Consistent Hashing

 - Akamai
 - BitTorrent
 - Amazon DynamoDB

# Hash Functions
Hash Functions are any functions that maps value from one arbitrary sized domain to a fixed sized values. The values output from the hash functions are typically used for efficient lookup of the original entity.

A very simple example of hash function is a `modulo N` function which operates on integers and returns the reminder when divided by `N` and thus generating the output values in the range `[0, N-1]`.

Recall  that  ahashfunctionmaps elements of a (usually super-big) universeU, like URLs, to “buckets,” suchas 32-bit values (Figure 1).  A “good” hash functionhsatisfies two properties:1.  It is easy to remember and evaluate.  Ideally, computing the function involves just afew arithmetic operations, and maybe a “mod” operation.2.  For all practical purposes,hbehaves like a totally random function,  spreading dataout evenly and without noticeable correlation across the possible buckets.

TODO: Image of hash functions

# Hashing in distributed system
SAy we are building a distrbiuted storage system where users can upload files and these files is stored on one of the storage machines. The storage machine where the file is stored depends on the name. Since there are so many fiels to tore, storing them on one machine does not make sense. Hence these files are stored across machines. THe mahcine that is responsible of holding the file depends on the name of the file.

Say we have 4 storage nodes we could do `h(name) % 4` where `h` is the hash function that takes a name and generate a 32 bit integer as the output. The integer is then mod with 4 to return the index of the storage node where the actual file is stored. NOw everytime a file is accessed by its name

```py
def get_file(name):
    node = storage_nodes[hash_fn(name) % 4]
    return node.fetch_file(name)
```

For things to scale smoothly, we need to constatly scale up the system and now when the number of storage nodes increases from 4 to say 7, the entire mapping changes. The same function does not work fine.

The file with hash value 1027 which was present on node C is now expected to be at node G. For most cases this mapping would change hence a lot of data needs to be migrated. This is super expensive. The solution to this problem is consistent hashing.

# Consistent Hashing
Our criticism of the solution (1) for mapping URLs to caches motivates the goal ofconsistenthashing:  we want hash table-type functionality (we can store stuff and retrieve it later) withthe  additional  property  that  almost  all  objects  stay  assigned  to  the  same  cache  even  asthe  numbernof  caches  changes.   We  next  give  the  most  popular  implementation  of  thisfunctionality 


Consistent Hashing provides an excellent way of load balancing items across nodes. There are lots of great resources to learn consistent hashing from and instead of reiterating things here we will implement it using an array based implementation.

# Consistent Hash as an array
Naive way is to create a hash space equal to ring_length length which could go huge and waste a lot of memory. Most of the elements are un occupued. Hence to fix that we take two arrays one holds the actual nodes that are present
while other holds the locations where you would find them on the ring.

The consistent hash as a ring could be treated as a sorted array. Given a node id or an item item, the hash function outputs an integer value that denotes the position of the entity in the hash space.

```py
def _generate_key(self, obj):
    """returns hash key modulo ring_length because of which it represents
    the location in the flattened hash ring where the data should reside.
    """
    if not obj:
        return None
    return hash_fn(obj) % self.ring_length
```

# Adding a node to the ring
When a new node is added to the ring, then we first need to find where the node will be placed on
the ring and then wo place it.

```py
def add_node(self, node_id: str) -> int:
    """add_node function adds a new node to the ring and returns the key
    from the hash space where it was placed
    """

    # handling error when hash space is full.
    if len(self._keys) == self.ring_length:
        raise Exception("hash space is full")

    key = self._generate_key(node_id)

    # find the index where the key should be inserted in the keys store
    index = bisect(self._keys, key)

    # if we have already seen the key i.e. node already is present
    # for the same key, we raise Collision Exception
    if index > 0 and self._keys[index - 1] == key:
        raise Exception("collision occurred")

    # insert the node_id and the key at the same `index` location.
    # this insertion will keep nodes and keys sorted w.r.t keys.
    self.nodes.insert(index, node_id)
    self._keys.insert(index, key)

    return key
```

# Removing a node from the hash

```py
def remove_node(self, node_id: str) -> int:
    """remove_node removes the node with id = node_id and returns the key
    from the hash space on which the node was placed.
    """

    # handling error when space is empty
    if len(self._keys) == 0:
        raise Exception("hash space is empty")

    key = self._generate_key(node_id)

    # we find the index where the key would reside in the keys
    index = bisect_left(self._keys, key)

    # if key does not exist in the array we raise Exception
    if index >= len(self._keys) or self._keys[index] != key:
        raise Exception("node does not exist")

    # now that all sanity checks are done we popping the
    # keys and nodes at the index and thus removing presence of the node.
    self._keys.pop(index)
    self.nodes.pop(index)

    return key
```

# Assigning a node to an item

```py
def assign(self, item_id: str) -> str:
    """Given an item, the function returns the node_id through which this
    item will be served.
    """
    key = self._generate_key(item_id)

    # we find the first right node to this key
    # if bisect_right returns index which is out of bounds then
    # we circle back to the first in the array - making it a ring
    index = bisect_right(self._keys, key) % len(self._keys)

    # return the node present at the index
    return self.nodes[index]
```

# References
 - [Hash Functions - Wikipedia](https://en.wikipedia.org/wiki/Hash_function)
 - [Consistent Hashin - Stanford](https://web.stanford.edu/class/cs168/l/l1.pdf)
