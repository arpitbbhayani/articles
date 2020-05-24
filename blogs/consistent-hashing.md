Consistent hashing is a hashing technique that performs really well when operated in a dynamic environment where the distributed system scales up and scales down frequently. The core concept of Consistent Hashing was introduced in the paper [Consistent Hashing and RandomTrees: Distributed Caching Protocols for Relieving Hot Spots on the World Wide Web](https://www.akamai.com/us/en/multimedia/documents/technical-publication/consistent-hashing-and-random-trees-distributed-caching-protocols-for-relieving-hot-spots-on-the-world-wide-web-technical-publication.pdf) but it gained popularity after the infamous paper introducing DynamoDB - [Dynamo: Amazon’s Highly Available Key-value Store](https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf). Since then the consistent hashing gained traction and found a ton of use cases in designing and scaling distributed systems efficiently. The two famous examples that exhaustively use this technique are Bit Torrent, for their peer-to-peer networks and Akamai, for their web caches. In this article we dive deep into the need of Consistent Hashing, the internals of it, and more importantly along the way implement it using arrays and [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm).

# Hash Functions
Before we jump into the core Consistent Hashing technique we first get a few things cleared up, one of which is Hash Functions. Hash Functions are any functions that map value from an arbitrarily sized domain to another fixed-sized domain, usually called the Hash Space. For example, mapping URLs to 32-bit integers or web pages' HTML content to a 256-byte string. The values generated as an output of these hash functions are typically used as keys to enable efficient lookups of the original entity.

An example of a simple hash function is a function that maps a 32-bit integer into an 8-bit integer hash space. The function could be implemented using the arithmetic operator `modulo` and we can achieve this by taking a `modulo 256` which yields numbers in the range `[0, 255]` taking up 8-bits for its representation. A hash function, that maps keys to such integer domain, more often than not applies the `modulo N` so as to restrict the values, or the hash space, to a range `[0, N-1]`.

A good hash function has the following properties
 - The function is computationally efficient and the values generated are easy for lookups
 - The function, for most general use cases, behaves like a pseudorandom generator that spreads data out evenly without any noticeable correlation

Now that we have seen what a hash function is, we take a look into how we could use them and build a somewhat scalable distributed system.

# Distributed storage system using traditional hashing
Say we are building a distributed storage system in which users can upload files and access them on demand. The service exposes the following APIs to the client

 - `upload` to upload the file to the storage machine
 - `fetch` to fetch the file and return its content

Behind the scenes the system has Storage Nodes on which the files are stored and accessed. These nodes exposes the function `put_file` and `fetch_file` that puts and gets the file content from the disk and sends it to the main API server which in turn sends the response back to the user.

To sustain the initial load, the system has 5 Stogare Nodes which stores the uploaded files in a distributed manner. Having multiple nodes ensures that the system, as a whole, is not overwhelmed, and the storage is distributed almost evenly across.

When the user invokes `upload` function with the path of the file, the system first needs to identify the storage node that will be responsible for holding the file and we do this by applying a hash function to the path and in turn getting the storage node index. Once we get the storage node, we read the content of the file and put that file on the node by invoking `put_file` function of the node.

```py
# storage_nodes holding instances of actual storage node objects
storage_nodes = [
    StorageNode(name='A', host='10.131.213.12'),
    StorageNode(name='B', host='10.131.217.11'),
    StorageNode(name='C', host='10.131.142.46'),
    StorageNode(name='D', host='10.131.114.17'),
    StorageNode(name='E', host='10.131.189.18'),
]


def hash_fn(key):
    """The function sums the bytes present in the `key` and then
    take a mod with 5. This hash function thus generates output
    in the range [0, 4].
    """
    return sum(bytearray(key.encode('utf-8'))) % 5


def upload(path):
    # we use the hash function to get the index of the storage node
    # that would hold the file
    index = hash_fn(path)

    # we get the StorageNode instance
    node = storage_nodes[index]

    # we put the file on the node and return
    return node.put_file(path)


def fetch(path):
    # we use the hash function to get the index of the storage node
    # that would hold the file
    index = hash_fn(path)

    # we get the StorageNode instance
    node = storage_nodes[index]

    # we fetch the file from the node and return
    return node.fetch_file(path)
```

The hash function used over here simply sums the bytes and takes the modulo by `5` and thus generating the output in range `[0, 4]`. This output value now represents the index of the storage engine that will be responsible for holding the file. Pseudocode representing the above flow of putting and fetching the file is illustrated below.

We have 5 files 'f1.txt', 'f2.txt', 'f3.txt', 'f4.txt', 'f5.txt' if we apply the hash function to these files we realize that they are stored on storage nodes E, A, B, C, and D respectively.

Things become interesting when the system gains good traction and we scale the storage node horizontally and want to make 7 nodes instead of 5. The hash function will change and now instead of doing a `mod 5` it would do `mod 7`. Changing the hash function implies changing the mapping and association of files with storage nodes. Let us first administer the new associations and see which files required to be moved.

If we apply the hash function to the same 5 files we get that files 'f1.txt', 'f2.txt', 'f3.txt', 'f4.txt', 'f5.txt' will now be stored on nodes D, E, F, G, A which means we need to move every single of the 5 files to different nodes and then only we can change the hash function.

![File association changed](https://user-images.githubusercontent.com/4745789/82738059-b9e6a100-9d52-11ea-8cf3-f264b4a195b1.png)

If we need to move not all but even half the amount of data, every time we scale up, the process of scaling up becomes super expensive and in longer run very tedious. This is where Consistent Hashing kicks in and ensures that when we scale up or down we only migrate a bare minimum amount of data to different nodes.

# Consistent Hashing
The main advantage we seek by using Consistent Hashing is that almost all the objects stay assigned to the same storage node even as the number of nodes change, either we scale up or down.

In a system desigined through the tradtional hashing techniques, we see that the Hash Space is equal to the number of slots i.e. storage nodes and on which our items i.e. files gets mapped to. When the number of slots i.e. nodes change the entire mapping changes and this is where the bottleneck lies.

Consistent Hashing addresses this situation by keeping the Hash Space huge and constant, in order of `[0, 2^256 - 1]` and the storage node and objects both map to one of the slots in this huge Hash Space. Now since the chances of item being hashed to the slot of storage node is infinitesimally small, the item is ampped to the storage node which is to the right of the hashed location.



Naive way is to create a hash space equal to ring_length length which could go huge and waste a lot of memory. Most of the elements are un occupued. Hence to fix that we take two arrays one holds the actual nodes that are present while other holds the locations where you would find them on the ring.

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
 - [Consistent Hashing - Stanford](https://web.stanford.edu/class/cs168/l/l1.pdf)
