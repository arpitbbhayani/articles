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
