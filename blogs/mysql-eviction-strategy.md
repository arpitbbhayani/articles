Disk reads are 4x (for SSD) to 80x (for magnetic disk) [slower](https://gist.github.com/hellerbarde/2843375) as compared to memory (RAM) access and hence it becomes extremely important for a database to utilize main memory as much as it can, and be super-performant while keeping its latencies to a bare minimum. Engines cannot simply replace disks with RAM because of volatility and cost, hence it needs to strike a balance between the two - maximize main memory utilization and keep the disk access to a bare minimum.

The database engine virtually splits the storage into pages. A page is a unit which represents how much data the engine transfers at any one time between disk (the data files) and memory (cache). It is usually a few kilobytes 4KB, 8KB, 16KB, 32KB and is configurable via some engine parameter. Thus a page can hold one or multiple rows of a table depending on how much data is in each row i.e. the length of row.

# Locality of reference
Database systems exhibit a strong and predictable behaviour called [locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference) which suggests access pattern of a page and its neighbours.

## Spatial Locality of Reference
Spatial locality of reference suggests if a row is accessed, it is very likely that the neighbouring rows will be accessed in the near future.

Having a larger page size addresses this situations. A larger page size implies more rows could fit in one page and if that page is cached in memory, when the next row is accessed the same page will be referenced from the memory thus saving a disk read.

## Temporal Locality of Reference
Temporal locality of reference suggests that if a page is recently accessed (referenced), it is very likely that the same page will be accessed (referenced) again in the near future.

Caching exploits this behaviour by putting every single page accessed from the disk into main-memory (cache) and the next time the same page is referenced, it returns the page from the cache, thus saving a disk read. The control flow of how a disk read happens could be represented as

![Disk cache control flow](https://user-images.githubusercontent.com/4745789/80286130-45b2e080-8747-11ea-9ea7-0fcb3235d809.png)

Since cache is limited, it can only hold some fixed number of pages, hence when the cache gets full the engine needs to decide which page should be moved out of the cache so that the new page could fit in. The most common strategy is the [Least Recently Used Cache eviction strategy](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)).

# The LRU Cache

---

Since cache is limited, hence when it gets full some elements of it should be removed making space of new hot items from the disk. This is cache eviction.

IMage: Control Flow.

In this article we will how MySQL's InnoDB database engine performs Cache Eviction and how this strategy solves a super critical problem in one of the most elegant ways.

# The usual LRU Cache

Most common way of implementing a cache is a Least Recently Used based Cache.
Belady's anomaly.
What is the problem.

# Midpoint Insertion Strategy

# References



-------------------------------

# Why does a database need cache?
As established earlier, disk reads are costly hence database engines stores frequently accessed pages in memory so that when the page is requested, instead of making a slower disk read, the engine can directly serve it from the main memory - cache.

## What if Database does not cache?
Not only does this hurt performance when a record is retrieved, we pay the same time cost if that same record is requested again..

Hence it makes sense of the database to cache whatever page has been read from the disk.

IMAGE: The control flow.

Now that we have established, the need of the cache, we see how this cache is implemented in 

# Buffer Pools
a series of buffers (memory locations) used by a program to cache disk dataBasically, the buffer pool is just a collection records, stored in RAM.When a record is requested, the program first checks to see if the record is in the pool.If so, there’s no need to go to disk to get the record, and time is saved.When the program does retrieve a record from disk, the newly-read record is copied into the pool, replacing a currently-stored record if necessary

# What happens during sequential scans?

# Midpoint Insertion Strategy

# References

---


In order to make I/O efficient, all database engines transfers data, to and from disk, in a batch of few kilobytes usually referred as a `page`. Once the page is read from the disk, it is stored in an in-memory data structure which acts as a cache. When the same page is referred again, the first check is made against the cache, if the page is present in the cache, it is returned from there, otherwise a disk seek is made retrieving a fresh copy of the page from the disk.

The overall process of fetching the page could be summarized as

IMAGE

This cache in MySQL InnoDB is called [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html) which caches the table and index data as it is accessed.


Dealing with disk in "page" is a much better 


Engines need to do this because of two major reasons

 - Cost of access
 - Locality of reference

Transacting pages, to and from disks, is an efficient way to overcome the above solutions.


Memory access is roughly 30 times faster than SSD disk access.

hence database usually cache the pages that it reads from the disk.

A unit of data transfer for any database engine is `Page` - usually a few kilobytes. This is how much the database engine transfers at any one time between disk and memory. A page can contain one or more rows, depending on how much data is in each row.

All the InnoDB disk data structures within a MySQL instance share the same page size. 



# Buffer Pool
The buffer pool is an area in main memory where InnoDB caches table and index data as it is accessed. The buffer pool permits frequently used data to be processed directly from memory, which speeds up processing. On dedicated servers, up to 80% of physical memory is often assigned to the buffer pool.

For efficiency of high-volume read operations, the buffer pool is divided into pages that can potentially hold multiple rows. For efficiency of cache management, the buffer pool is implemented as a linked list of pages; data that is rarely used is aged out of the cache using a variation of the LRU algorithm.

Knowing how to take advantage of the buffer pool to keep frequently accessed data in memory is an important aspect of MySQL tuning. 



COmparing time taken from various stores - in-memory vs ssd


# References

 - [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html)
 - [Making the Buffer Pool Scan Resistant](https://dev.mysql.com/doc/refman/8.0/en/innodb-performance-midpoint_insertion.html)
 - [Latency numbers](https://gist.github.com/hellerbarde/2843375)
 - [Locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference)
