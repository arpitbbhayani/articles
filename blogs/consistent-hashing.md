Consistent hashing is a hashing technique that performs really well when operated in a dynamic environment where the number of keys mapped to change frequently. The core concept of Consistent Hashing was introdured in the paper [Consistent Hashing and RandomTrees : Distributed Caching Protocols for Relieving Hot Spots on the World Wide Web](https://www.akamai.com/us/en/multimedia/documents/technical-publication/consistent-hashing-and-random-trees-distributed-caching-protocols-for-relieving-hot-spots-on-the-world-wide-web-technical-publication.pdf) but was made really famous after the infamous white paper of dynamodb [Dynamo: Amazon’s Highly Available Key-value Store](https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf). Since them consistent hashing did not look back and started gaining traction and found a ton of use cases while desinging and scaling distributed systems. Two famous examples that exhaustively uses consistent hashing are Bit Torrent and Akamai. In this article we dive deep into Consistent Hashing and more importantly along the way also implement it using the simplest compose data type - array.

# Hash Functions
Before we jump into the core Consistent Hashing technique we first get few things cleared up one of which is Hash Functions. Hash Functions are any functions that maps value from one arbitrary sized domain to another fixed sized domain values. For example: mapping URLs to 32 bit integers or web pages to 256 byte strings. The values generated as an output of these hash functions are typically used as keys to make lookups of original entity efficient and the store that holds all such keys is called a Hash Table.

A very simple hash function maps any 32 bit integer to a 8 bit integer and the way we can do this is by taking a `modulo 256`. A hash function more often than not applies the `modulo N` so as to restrict the domain values to a range `[0, N-1]`.

TODO: Image of hash functions

A good hash function has following properties

 - The function is computationally efficient and easy to evaluate and also easy for lookups.
 - The function, for most cases behaves like a pseudorandom function spreading data out evenly without any noticeable correlation.

Now that we have seen what a hash function is we take a look into how traditional hash functions fit into our real world.

# Hashing in distributed system
Say we are building a distrbiuted storage system within which users can upload files and these files are stored on one of the 5 storage machines so that we distribute the load properly. We use hash function to decide which storage machine would store which file and the function would use the file name and spit out an integer in the range `[0, 4]` denoting the index of storage node that would hold that file. A pseudocode representing the above flow of fetching the file through function `fetch_file` is as illustrated bwlow.

```py
# storage_nodes holding programmatic instances of actual storage node
# Each of the node has a `fetch_file` function exposed which actually
# fetches the file from the corresponding machine.
storage_nodes = [
    StorageNode(name='A', host='10.131.213.12'),
    StorageNode(name='B', host='10.131.217.11'),
    StorageNode(name='C', host='10.131.142.46'),
    StorageNode(name='D', host='10.131.114.17'),
    StorageNode(name='E', host='10.131.189.18'),
]

def hash_fn(key):
    """The function applies some transformation function on the
    key and generate an integer value. This value is then mod 5 so
    that we point to one of the 5 storage nodes to put or fetch data.
    """
    return fn(name) % 5


def fetch_file(name):
    # we use the hash function to get the index of the storage node
    # that would hold the file
    index = hash_fn(name)

    # we get the StorageNode instance
    node = storage_nodes[index]

    # we fetch the file from the node and return
    return node.fetch_file(name)
```

Since the hash function works in a pseudorandom way we expect it to distribute load evenly across the 5 storgae nodes and hence ensure we maintain our SLA and serve the customers well.

Things become interesting when the system is a hit and we need to scale the product, now 5 storage machines are not enough and we need to add say 2 more nodes. Now with this implementation things look pretty bleak. For things to scale smoothly, we need to constatly scale up the system and now when the number of storage nodes increases from 4 to say 7, the entire mapping changes. The same function does not work fine.

TODO: Remapping of files across nodes IMAGE - OLD and new with file examples.

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
