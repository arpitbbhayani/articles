Consistent Hashing provides an excellent way of load balancing items across nodes. There are lots of great resources to learn consistent hashing from and instead of reiterating things here we will implement it using an array based implementation.

# Consistent Hash as an array
Naive way is to create a hash space equal to hash_space length which could go huge and waste a lot of memory. Most of the elements are un occupued. Hence to fix that we take two arrays one holds the actual nodes that are present
while other holds the locations where you would find them on the ring.

The consistent hash as a ring could be treated as a sorted array. Given a node id or an item item, the hash function outputs an integer value that denotes the position of the entity in the hash space.

```py
def _generate_key(self, obj):
    """returns hash key modulo hash_space because of which it represents
    the location in the flattened hash ring where the data should reside.
    """
    if not obj:
        return None
    return hash_fn(obj) % self.hash_space
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
    if len(self._keys) == self.hash_space:
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

# Assigning a node to an item

# References
