A common strategy to make any system super-performant is *[Caching](https://en.wikipedia.org/wiki/Cache_(computing)).* Almost all software products, operating at scale, have multiple layers of caches in their architectures. Caching, when done right, does wonder to the response time and is one of the main reasons why products work so well on a massive scale. Cache engines are limited by the amount of memory available and hence once it gets full the engine has to decide which item should be evicted and that is where an eviction algorithm, like [LFU](https://en.wikipedia.org/wiki/Least_frequently_used) and LRU. kicks in.

[LRU](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)) (Least Recently Used) cache eviction strategy is one of the most popular strategies out there. LFU (Least Frequently Used) strategy fares well in some use cases but a concern with its most popular implementation, where it uses a min-heap, is that it provides a running time complexity of `O(log n)` for all the three operations - insert, update and delete; because of which, more often than not, it is replaced with a sub-optimal yet extremely fast `O(1)` LRU eviction scheme.

In this essay, we take a look at Constant Time LFU implementation based on the paper [An O(1) algorithm for implementing the LFU cache eviction scheme](http://dhruvbird.com/lfu.pdf) by Prof. Ketan Shah, Anirban Mitra and Dhruv Matani, where instead of using a min-heap it uses a combination of [doubly linked lists](https://en.wikipedia.org/wiki/Doubly_linked_list) and [hash table](https://en.wikipedia.org/wiki/Hash_table) to gain a running time complexity of `O(1)` for all the three core operations.

# The LFU cache eviction strategy

LFU, very commonly, is implemented using a [min-heap](https://en.wikipedia.org/wiki/Min-max_heap) which is organized as per the frequency of access of each element. Each element of this heap holds a pair - cached value and the access frequency; and is structured in order of this frequency such that the cached value with the minimum access frequency sits at the top, making it quick to identify the element to be evicted.

![https://user-images.githubusercontent.com/4745789/89717235-0fd1f900-d9d2-11ea-968d-9ed67f52a2db.png](https://user-images.githubusercontent.com/4745789/89717235-0fd1f900-d9d2-11ea-968d-9ed67f52a2db.png)

Although the identification of the element to be evicted is quick, but in order for the heap to maintain its property - element with lowest access frequency be at the top - it demands a rebalance; and this rebalancing process has a running complexity of `O(log n)`. To make things worse, rebalancing is required every single time the frequency of an item is changed; which means that in the cache that implements LFU, every time an item is either inserted, accessed or evicted, it demands a rebalance - making all the three core operations `O(log n)`.

# Constant time implementation

The LFU cache can be implemented with `O(1)` complexity for all the three operations by using one [Hash Table](https://en.wikipedia.org/wiki/Hash_table) and a bunch of [Doubly Linked Lists](https://en.wikipedia.org/wiki/Doubly_linked_list). As stated by the [RUM Conjecture](https://arpitbhayani.me/blogs/rum), in order to get faster - constant time `O(1)` - reads and updates we have to make a compromise with the memory utilization and we observe exactly that in this implementation.

## The Hash Table

The Hash Table stores the mapping of the cached key to the Value Node holding the cached value. The value against the key is usually a pointer to the actual Value Node. Given that the lookup complexity of the hash table is `O(1)`  operation to access the value given the key from this Hash Table could be accomplished in constant time.

![https://user-images.githubusercontent.com/4745789/90469594-e2561f80-e136-11ea-9ff4-8369a7ea3df3.png](https://user-images.githubusercontent.com/4745789/90469594-e2561f80-e136-11ea-9ff4-8369a7ea3df3.png)

The illustration above depicts the Hash Table holding cache keys `k1`, `k2`, etc mapped to nodes holding the values `v1` and `v2` through direct pointers. The nodes are allocated on the heap using dynamic allocation could be a little disorganized. The Value Node to which the key maps to, not only hold the cached value, but it also holds a bunch of pointers pointing to different entities in the system, as discussed later.

## Doubly Linked Lists

This implementation of LFU requires us to maintain one Doubly Linked List of frequencies holding one node for each unique frequency spanning all the caches values. This list is kept sorted on the access frequency such that the node representing the lowest frequency is on the one end while the node representing the highest frequency is at the other.

Every frequency node holds the frequency that it represents `freq` and the usual `next` and `prev` pointers pointing to the adjacent frequency nodes; it also keeps a `values_ptr` which points to another doubly linked list of nodes holding Value Nodes (referred in the hash table) having the same access frequency `freq`.

![https://user-images.githubusercontent.com/4745789/90469593-e08c5c00-e136-11ea-995b-e4590981dd89.png](https://user-images.githubusercontent.com/4745789/90469593-e08c5c00-e136-11ea-995b-e4590981dd89.png)

The overall schematic representation of doubly-linked lists and its arrangement is as shown in the illustration above. The doubly linked list holding frequency nodes is arranged horizontally while the list holding the Value Nodes is arranged vertically.

Since the cached values `v1` and `v7` both have been accessed 7 times they both are chained in a double linked list and are hooked with the frequency node for frequency `7`. Similarly, the value nodes holding values `v5`, `v3`, and `v9` are chained in another doubly linked list and are hooked with the frequency node representing frequency `18`.

The value node contains the cached value `data`, along with the usual `next` and `prev` pointers pointing to the adjacent value nodes in the list. It also holds a `freq_pointer` pointing to the frequency node to which it belongs. Having all of these pointers helps us ensure all the three operations happen in constant time.

Now that we have established all the necessary structures in place, we take a look at the core 3 operations along with their pseudo implementation.

## Adding value to the cache

While inserting the value in the cache, we first check the existence of the key in the table, if so we raise the error stating key is already present. Once we are sure to add the key and value in the cache we ensure that the frequency node representing the frequency of `1` is present and then we add the value wrapped in a value node to its `values_list`, and at last we make an entry in the table acknowledging the caching process.

```python
def add(key: str, value: object):
    # check if the key already present in the table,
    # if so then return the error
    if key in table:
        raise KeyAlreadyExistsError

    # create the value node out of value
    # holding all the necessary pointers
    value_node = make_value_node(value)

    first_frequency_node = freq_list.head
    if first_frequency_node.freq != 1:
        # since the first node in the freq_list does not represent
        # frequency of 1, we create a new node
        first_frequency_node = make_frequency_node(1)

        # update the `freq_list` that holds all the frequency nodes
        # such that the first node represents the frequency 1
        # and other list stays as is.
        first_frequency_node.next = freq_list.head
        freq_list.head.prev = first_frequency_node
        freq_list.head = first_frequency_node

    # value node points back to the frequency node to which it belongs
    value_node.freq_pointer = first_frequency_node

    # add the value node in `first_frequency_node`
    first_frequency_node.values.add(value_node)

    # update the entry in the hash table
    table[key] = value_node
```

As seen in the pseudocode above the entire procedure to add a new item in the cache is a bunch of memory allocation along with pointer manipulations, hence we observe that the running complexity of `add` is `O(1)`.

## Evicting an item from the cache

For evicting an item we pick the item with the lowest access frequency which could be found as a first Value Node of the first Frequency Node in the frequency list. Since we keep the frequency list sorted as per the frequency count accessing the Frequency Node with the lowest frequency is done in constant time and the first value node belonging to it is flagged for eviction. The entire eviction process thus has a running complexity of `O(1)`

```python
def evict():
    if freq_list.head and freq_list.head.values:
        first_value_node = freq_list.head.values.first
        second_value_node = first_value_node.next

        # make the second element as first
        freq_list.head = second_value_node

        # ensure second node does not have a dangling prev link
        second_value_node.prev = None

        # delete the first element
        delete_value_node(first_value_node)

    if freq_list.head and not freq_list.head.values:
        # if the frequency node after eviction does not hold
        # any values we get rid of it
        delete_frequency_node(freq_list.head)
```

## Getting a value from the cache

Access to an item from the cache has to be the most common operation that any cache has to support. In the LFU scheme, while returning the cached value, also has to update its access frequency. Making this entire process run with a constant time complexity requires a bunch of pointer manipulations.

The engine first makes a get call to the Hash Table ensuring that the key exists in the cache. But before returning the cached value from the value node, the engine needs to update the access frequency; and to do so it access the Frequency node and its sibling of the Value Node. Ensures that the frequency of the sibling is 1 more than that of the frequency node. Changes the affinity of the value node from the current frequency to the sibling's and sets the appropriate pointer connections and returns the value.

The entire flow, though looks complicated through text, is very simple to understand through code. Since this access function only deals with direct pointer manipulations, it has a constant running time complexity.

```python
def get(key: str) -> object:
    # get the value node from the hash table
    value_node = table.get(key, None)

    # if the value does not exist in the cache then return an error
    # stating Key Not Found
    if not value_node:
        raise KeyNotFoundError

    # we get the frequency node from the value node using the
    # freq_pointer member.
    frequency_node = value_node.freq_pointer

    # we also get the next frequency node to the current
    # frequency node so that we could make a call about
    # the need to create a new node.
    next_frequency_node = frequency_node.next

    if next_frequency_node.freq != frequency_node.freq + 1:
        # create a new frequency node
        new_frequency_node = make_frequency_node(frequency_node.freq + 1)
        
        # place the frequency node at the correct position in the list
        frequency_node.next = new_frequency_node
        new_frequency_node.prev = frequency_node

        next_frequency_node.prev = new_frequency_node
        new_frequency_node.next = frequency_node

        # going forward we call the new frequency node as next
        # because it represents the the next frequency node
        next_frequency_node = new_frequency_node

    # we add the value node in the nex
    next_frequency_node.values.add(value_node)
    
    # we change the parent and adjecent nodes to this value nodes
    value_node.freq_pointer = next_frequency_node
    value_node.next = None
    value_node.prev = next_frequency_node.values.last
    
    # if the frequency node has no elements then deleting the node
    # so as to avoid the memory leak
    if len(frequency_node.values) == 0:
        delete_frequency_node(frequency_node)

    # returning the value
    return value_node.value
```

# References

- [An O(1) algorithm for implementing the LFU cache eviction scheme](http://dhruvbird.com/lfu.pdf)
- [When and Why to use a Least Frequently Used (LFU) cache with an implementation in Golang](https://ieftimov.com/post/when-why-least-frequently-used-cache-implementation-golang/)