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

Behind the scenes the system has Storage Nodes on which the files are stored and accessed. These nodes expose the functions `put_file` and `fetch_file` that puts and gets the file content from the disk and sends it to the main API server which in turn sends the response back to the user.

To sustain the initial load, the system has 5 Stogare Nodes which stores the uploaded files in a distributed manner. Having multiple nodes ensures that the system, as a whole, is not overwhelmed, and the storage is distributed almost evenly across.

When the user invokes `upload` function with the path of the file, the system first needs to identify the storage node that will be responsible for holding the file and we do this by applying a hash function to the path and in turn getting the storage node index. Once we get the storage node, we read the content of the file and put that file on the node by invoking the `put_file` function of the node.

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

The hash function used over here simply sums the bytes and takes the modulo by `5` (since there are 5 storage nodes in the system) and thus generating the output in the hash space `[0, 4]`. This output value now represents the index of the storage engine that will be responsible for holding the file.

Say we have 5 files 'f1.txt', 'f2.txt', 'f3.txt', 'f4.txt', 'f5.txt' if we apply the hash function to these we find that they are stored on storage nodes E, A, B, C, and D respectively.

Things become interesting when the system gains some traction and it needs to be scaled to 7 nodes, which means now the hash function should do `mod 7` instead of a `mod 5`. Changing the hash function implies changing the mapping and association of files with storage nodes. We first need to administer the new associations and see which files required to be moved from one node to another.

With the new hash function the same 5 files 'f1.txt', 'f2.txt', 'f3.txt', 'f4.txt', 'f5.txt' will now be associated with storage nodes D, E, F, G, A. Here we see that changing the hash function requires us to move every single one of the 5 files to a different node.

![File association changed](https://user-images.githubusercontent.com/4745789/82746677-16c47480-9db0-11ea-8dea-7b5a3cb73e91.png)

If we have to change the hash function every time we scale up or down and if this requires us to move not all but even half of the data, the process becomes super expensive and in longer run infeasible. So we need a way to minimize the data movement required during scale-ups or scale-downs, and this is where Consistent Hashing fits in as it is designed to minimize this data transfer.

# Consistent Hashing
The main advantage we seek by using Consistent Hashing is that even when the system scales and we add more storage nodes, almost all the objects stay assigned to the same storage node. With this requirement in place we dissect the traditional hashing approach.

In a system designed through the traditional hashing techniques, we see that the Hash Space is always equal to the number of storage nodes and onto which our files get mapped to. When the number of storage nodes changes the entire mapping changes and this is where the bottleneck lies. We need to make a Hash function independent of the number of the storage node and we could solve this issue.

Consistent Hashing addresses this situation by keeping the Hash Space huge and constant, somewhere in the order of `[0, 2^256 - 1]` and the storage node and objects both map to one of the slots in this huge Hash Space. Unlike in the traditional system where the file was associated with storage node at index where it got hashed to, in this system the chances of a collision between a file and a storage node are infinitesimally small and hence we need a different way to define this association.

Since the chances of the file and storage node being hashed to the same location in this vast Hash Space is very small, we define the association as - the file will be associated with the storage node which is present to the immediate right of its hashed location. Defining association in this way helps us

 - keep the hash function independent of the storage nodes
 - associations are relative and do not require collisions

![Associations in Consistent Hashing](https://user-images.githubusercontent.com/4745789/82748149-4d54bc00-9dbd-11ea-8f06-6710a5c98f20.png)

A very naive way to implement this is by allocating an array of size equal to the Hash Space and putting files and storage node literally in the array on the hashed location. In order to get association we iterate from the item's hashed location towards the right and find the first Storage Node. If we reach the end of the array and do not fund any Storage Node we circle back to index 0 and continue the search. The approach is very easy to implement but suffers from the following limitations

 - requires huge memory to hold such a large array
 - finding association by iterating every time to the right is `O(hash_space)`

Since in the above approach, most of the items in the array are not allocated, we are wasting a lot of space. A better way of implementing this is by using two arrays: one to hold the Storage Nodes, called `nodes` and another one to hold the positions of the Storage Nodes in the hash space, called `keys`. There is a one-to-one correspondence between the two arrays as the Storage Node `nodes[i]` is present at position `keys[i]` in the hash space. Both the arrays are kept sorted as per the `keys` array.

## Hash Function in Consistent Hashing
We define `total_slots` as the size of this entire hash space, typically of order `2^256` and the hash function could be implemented by taking [SHA-256](https://en.wikipedia.org/wiki/SHA-2) followed by a `mod total_slots`. Since the `total_slots` is huge and a constant the following hash function implementation is independent of the actual number of Storage Nodes present in the system and hence remains unaffected by scaling up or down events.

```py
def hash_fn(key: str, total_slots: int) -> int:
    """hash_fn creates an integer equivalent of a SHA256 hash and
    takes a modulo with the total number of slots in hash space.
    """
    hsh = hashlib.sha256()

    # converting data into bytes and passing it to hash function
    hsh.update(bytes(key.encode('utf-8')))

    # converting the HEX digest into equivalent integer value
    return int(hsh.hexdigest(), 16) % total_slots
```

## Adding a new node in the system
When there is a need to scale up and a new node in the system, in our case a new Storage Node, we

 - find the position of the node where it resides in the Hash Space
 - populate the new node with data it is supposed to serve
 - add the node in the Hash Space

When a new node is added in the system it only affects the files that hash at the location to the left and and associated with the node to the right, of the position the new node will fit in. All other files and associations remain intact, thus minimizing the amount of data to be migrated and mapping required to be changed.

![Adding a new node in the system - Consistent Hashing](https://user-images.githubusercontent.com/4745789/82749683-80507d00-9dc8-11ea-92a5-5ed9ebeacd69.png)

From the illustration above we see, when the new node K is added between nodes B and E, we find all the files that are mapped to node E and are hashed at index that lies before node K. These are the files whose association will be changed from E to the newly added node K. Hence the node K is populated with the required contents and then added in the hash space.

In order to implement this at low level using `nodes` and `keys` array, we get the index where the new node will fit in. Then using binary search we find the index of this position in the `keys` array and on this position insert the new storage node in `nodes` array and key in `keys` array.

```py
def add_node(self, node: StorageNode) -> int:
    """add_node function adds a new node in the system and returns the key
    from the hash space where it was placed
    """

    # handling error when hash space is full.
    if len(self._keys) == self.total_slots:
        raise Exception("hash space is full")

    key = hash_fn(node.host, self.total_slots)

    # find the index where the key should be inserted in the keys array
    # this will be the index where the Storage Node will be added in the
    # nodes array.
    index = bisect(self._keys, key)

    # if we have already seen the key i.e. node already is present
    # for the same key, we raise Collision Exception
    if index > 0 and self._keys[index - 1] == key:
        raise Exception("collision occurred")

    # insert the node_id and the key at the same `index` location.
    # this insertion will keep nodes and keys sorted w.r.t keys.
    self.nodes.insert(index, node)
    self._keys.insert(index, key)

    return key
```

# Removing a node from the hash
```py
def remove_node(self, node: StorageNode) -> int:
    """remove_node removes the node and returns the key
    from the hash space on which the node was placed.
    """

    # handling error when space is empty
    if len(self._keys) == 0:
        raise Exception("hash space is empty")

    key = hash_fn(node.host, self.total_slots)

    # we find the index where the key would reside in the keys
    index = bisect_left(self._keys, key)

    # if key does not exist in the array we raise Exception
    if index >= len(self._keys) or self._keys[index] != key:
        raise Exception("node does not exist")

    # now that all sanity checks are done we popping the
    # keys and nodes at the index and thus removing the presence of the node.
    self._keys.pop(index)
    self.nodes.pop(index)

    return key
```

# Assigning a node to an item
```py
def assign(self, item: str) -> str:
    """Given an item, the function returns the node_id through which this
    item will be served.
    """
    key = hash_fn(item, self.total_slots)

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
