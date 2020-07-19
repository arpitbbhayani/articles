Bitcask is one of the most efficient embedded Key Value (KV) Databases designed to handle production-grade traffic. The paper that introduced Bitcask to the world says it is a [*Log-Structured](https://en.wikipedia.org/wiki/Log-structured_file_system) [Hash Table](https://en.wikipedia.org/wiki/Hash_table) for Fast Key/Value Data* which, in short, means that the data will be written sequentially to an append-only log file and there will be pointers for each `key` pointing to the `position` of its log entry. Building a KV store off the append-only log files seems like a really weird design choice, but Bitcask does not only make it efficient to do so but it also gives a really high Read and Write throughput.

Bitcask was introduced as the backend for a distributed database named [Riak](https://riak.com/) in which each node used to run one instance of Bitcask to hold the data that it was responsible for. In this essay we take a detailed look into Bitcask, its design and find its secret sauce that make it so performant.

# Design of Bitcask

Bitcask uses a lot of principles from [log-structured file systems](https://en.wikipedia.org/wiki/Log-structured_file_system) and draws inspiration from a number of designs that involve log file merging ex: LSM Trees. It essentially is just a directory of append-only (log) files with a fixed structure and an in-memory index holding the keys mapped to a bunch of information necessary for point lookup - referring to the entry in the datafile.

## Datafiles

Datafiles are the append-only log files that holds the KV pairs along with some meta information. A single Bitcask instance could have many datafiles out of just one will be active and opened for writing while the others are considered immutable and are used for reads.

![https://user-images.githubusercontent.com/4745789/87866701-78fdb800-c9a2-11ea-9c35-9a706ac96d97.png](https://user-images.githubusercontent.com/4745789/87866701-78fdb800-c9a2-11ea-9c35-9a706ac96d97.png)

Each entry in the datafile has a fixed structure illustrated above and it stores `crc`, `timestamp`, `key_size`, `value_size`, `key` and `value`. All the write create, update and delete requests to the engine translates into entries in this active datafile. When this active datafile meets a size threshold, it is closed and a new active datafile is created; and as stated earlier, when closed the datafile is considered immutable and is never opened for writing again.

## KeyDir

KeyDir is an in-memory hash table that stores all the keys present in the Bitcask instance and maps it to the offset in the datafile where the value resides; thus facilitating the point lookups. The mapped value of the Hash Table is a structure that holds `file_id`, `offset` and some meta information like `timestamp`, as illustrated below.

![https://user-images.githubusercontent.com/4745789/87866707-96cb1d00-c9a2-11ea-9730-fc7f8cb79b92.png](https://user-images.githubusercontent.com/4745789/87866707-96cb1d00-c9a2-11ea-9730-fc7f8cb79b92.png)

# Operations on Bitcask

Now that we have seen the overall design and components of Bitcask, we can jump into understanding that operations that it supports and how each one is implemented.

### Putting a new Key Value

When a new KV pair is submitted to be stored in the Bitcask, the engine appends first it to the active datafile and then creates a new entry in the `KeyDir` specifying the offset and file where the value is stored. Both of these actions are performed atomically which means either the entry is made in both the structures or none.

Putting a new Key-Value pair requires just one atomic operation encapsulating one disk write and a few in-memory access and updates. Since the active datafile is an append-only file, the disk write operation does not have to perform any disk seek whatsoever making write operate at optimum rate providing a high write throughput.

### Updating an existing Key Value

KV stores does not support partial update but it does support full value replacement. Hence the update operation looks is very similar to putting a new KV pair, the only change being instead of creating an entry in KeyDir, the existing entry is updated with the new position in the new datafile.

The entry corresponding to the old value is now dangling and will be garbage collected explicitly.

### Deleting a Key

Deleting a key is a special operation where the engine atomically appends a new entry in the active datafile with value equalling a tombstone value, denoting deletion, and deleting the entry from the KeyDir. The tombstone value is chosen something very unique so that it does not interfere with existing value space of the use-case.

Delete operation just like update operation is lightweight and requires a disk write and an in-memory update and hence provides a very high throughput. Just like in updates, the older entries for the keys will be garbage collected explicitly.

### Reading a Key Value

Reading a KV pair from the store requires the engine to first find the datafile and the offset within it for the given key; which is done using the KeyDir. Once that information is available the engine then performs one disk read from the file at the offset to retrieve the log entry. The correctness of the value retrieved is checked against the CRC stored and the value is returned.

The operation is inherently fast as it requires just one disk read and a few in-memory accesses, but it could be made faster using Filesystem read-ahead cache.

# Merge and Compaction

As we have seen during Update and Delete operations the old entries corresponding to the key in datafiles remain as is and this leads to Bitcask consuming a lot of disk space. In order to make things efficient for the disk utilization the engine once a while compacts the older closed datafiles into one or many merged files.

The merge process iterates over all the immutable files in the Bitcask and produces a set of datafiles having only live and latest versions of each present key. This way the unused and non-existent keys are deleted from the datafiles saving us a bunch of disk space. Now since the record instead of lying datafiles resides at a new location in merged and compacted file, its entry in KeyDir needs to be atomically updated.

# Performant bootup

If the Bitcask crashes and it needs to boot-up, it will have to read all the datafiles and create a new KeyDir. Merging and compaction here does help as it reduces the need to read data that is eventually going to be evicted. But there is another operation that could help in making faster boot times.

For every datafile a *hint* file is created which holds everything in the datafile except the value i.e. it holds the key and its meta information. This *hint* file for a datafile is hence just a file containing all the keys from the datafile. The hint file is considerably very small in size and hence by reading this file the engine could quickly create the KeyDir and complete the bootup process.

# Strengths and Weaknesses of Bitcask

## Strengths

Going by the 

- Low latency for read and write operations
- High Write Throughput
- Single disk seek to retrieve any value
- Predictable lookup and insert performance
- Crash recovery is fast and bounded
- Backing up is easy - Just copy the directory

## Weakness

The KeyDir holds all the keys in memory at all times and this adds a huge constraint on the system that it needs to have enough memory to contain the entire keyspace along with from Filesystem buffers.

But if we reach the limit of vertical scalaing we can always shard and scale it horizontally without loosing much of the basic operations like Create, Read, Update and Delete.

# References

- [Bitcask Paper](https://riak.com/assets/bitcask-intro.pdf)
- [Bitcask - Wikipedia](https://en.wikipedia.org/wiki/Bitcask)
- [Riak's Bitcask - High Scalability](http://highscalability.com/blog/2011/1/10/riaks-bitcask-a-log-structured-hash-table-for-fast-keyvalue.html/)
- [Implementation of the Bitcask storage model-merge and hint files](https://topic.alibabacloud.com/a/implementation-of-the-bitcask-storage-model-merge-and-hint-files_8_8_31516931.html)
