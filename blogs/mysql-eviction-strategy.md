Disk reads are 4x (for SSD) to 80x (for magnetic disk) [slower](https://gist.github.com/hellerbarde/2843375) as compared to main-memory (RAM) and hence it becomes extremely important for a database to utilize main-memory as much as it can, and be super-performant while keeping its latencies to a bare minimum. Engines cannot simply replace disks with RAM because of volatility and cost, hence it needs to strike a balance between the two - maximize main-memory utilization and minimize the disk access.

The database engine virtually splits the data files into pages. A page is a unit which represents how much data the engine transfers at any one time between the disk (the data files) and the main-memory. It is usually a few kilobytes 4KB, 8KB, 16KB, 32KB, etc. and is configurable via parameters. Because of its bulky size a page can hold one or multiple rows of a table depending on how much data is in each row i.e. the length of row.

# Locality of reference
Database systems exhibit a strong and predictable behaviour called [locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference) which suggests an access pattern of a page and its neighbours.

## Spatial Locality of Reference
Spatial locality of reference suggests if a row is accessed, there is a high probability that the neighbouring rows will be accessed in the near future.

Having a larger page size addresses this situation to some extent. As one page could fit multiple rows, this means when that page is cached in memory, the engine saves a disk read if the neighbouring rows lying in the same page are accessed. Another approach to take advantage of this behaviour is to [read-ahead](https://dev.mysql.com/doc/refman/8.0/en/innodb-disk-io.html) that pages that are very likely to be accessed in the future and keep them available in the main-memory (cache).

## Temporal Locality of Reference
Temporal locality of reference suggests that if a page is recently accessed, it is very likely that the same page will be accessed again in the near future.

Caching exploits this behaviour by putting every single page accessed from the disk into main-memory (cache). Hence the next time the same page is referenced it is available in the main-memory eradicating the need of a disk read.

![Disk cache control flow](https://user-images.githubusercontent.com/4745789/80286313-4e57e680-8748-11ea-88c2-dcb67f6ac566.png)

Since cache is bounded and limited in size, it can only hold some fixed number of pages, hence when the cache gets full the engine needs to decide which page should be moved out of the cache so that the new page could fit in. The most common strategy is the [Least Recently Used Cache eviction strategy](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)), that helps in deciding which page to evict by considering how recently that page was accessed.

# The LRU Cache
The LRU cache holds the items in the order of its access allowing us to identify which item is not being used the longest. When the cache is full and a newer item needs to make an entry in the cache, the item which is not accessed the longest is evicted and hence the name Least Recently Used.

## Implementation
An LRU cache is often implemented by pairing a [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) with a [hash map](https://en.wikipedia.org/wiki/Hash_table). The cache is thus just a linked list of pages while the hashmap mapping the `page_id` to the node in the linked list.

The most-recently referenced page is at the head of the list while the least-recently referenced one is at the tail. When a new page is to be added to the list it gets added to the head while the eviction always happens on the tail end of it. If a page exists in the cache and is accessed again, it is brought back to the head of the list as it is now the most recently referenced page.

![LRU Cache](https://user-images.githubusercontent.com/4745789/80288324-d7751a80-8754-11ea-96ab-6a8e25730bff.png)

## Benefits of Cache
Show that the grass is green.

## Issue with this implementation
MySQL's InnoDB uses this LRU mechanism by default to manage the pages within the cache, which means everytime the InnoDB engine accesses a page on the disk, it adds the page in this cache and if required evicts one page from the cache. The problem arises when an entire table is scanned, this usually happens while [taking a data dump](https://dev.mysql.com/doc/refman/8.0/en/mysqldump.html) or while executing a `SELECT` query with no `WHERE` clause.

Such statements pulls a large amount of data, almost an entire table, in cache, and displacing existing data from cache. The worst part here is that this freshly loaded data is never ever refereced again, which means the performance of the database is going to take a huge hit.

```
OLTP server with a warm buffer pool containing the current working set. Then someone submit a report needing to access a table through a full table scan. The normal and current MySQL behavior is to wipe out the content of the cache. if the table is never reused this is pure loss

The technique of initially bringing pages into the InnoDB buffer pool not at the "newest" end of the list, but instead somewhere in the middle. The exact location of this point can vary, based on the setting of the innodb-old-blocks-pct option. The intent is that blocks that are only read once, such as during a full table scan, can be aged out of the buffer pool sooner than with a strict LRU algorithm. 

An acronym for "least recently used", a common method for managing storage areas. The items that have not been used recently are evicted when space is needed to cache newer items. InnoDB uses the LRU mechanism by default to manage the pages within the buffer pool, but makes exceptions in cases where a page might be read only a single time, such as during a full table scan. This variation of the LRU algorithm is called the midpoint insertion strategy. The ways in which the buffer pool management differs from the traditional LRU algorithm is fine-tuned by the options innodb-old-blocks-pct, innodb_old_blocks_time, and the new MariaDB 5.6 options innodb_lru_scan_depth and innodb_flush_neighbors. 
```

# Midpoint Insertion Strategy

"Midpoint insertion strategy" which makes things not a true LRU in order to deprioritize superfluous pages.

but makes exceptions in cases where a page might be read only a single time, such as during a full table scan. This variation of the LRU algorithm is called the midpoint insertion strategy.



---

# The usual LRU Cache

Most common way of implementing a cache is a Least Recently Used based Cache.
Belady's anomaly.
What is the problem.

# Midpoint Insertion Strategy

# References



-------------------------------

# Why does a database need cache?
As established earlier, disk reads are costly hence database engines stores frequently accessed pages in memory so that when the page is requested, instead of making a slower disk read, the engine can directly serve it from the main-memory - cache.

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
The buffer pool is an area in main-memory where InnoDB caches table and index data as it is accessed. The buffer pool permits frequently used data to be processed directly from memory, which speeds up processing. On dedicated servers, up to 80% of physical memory is often assigned to the buffer pool.

For efficiency of high-volume read operations, the buffer pool is divided into pages that can potentially hold multiple rows. For efficiency of cache management, the buffer pool is implemented as a linked list of pages; data that is rarely used is aged out of the cache using a variation of the LRU algorithm.

Knowing how to take advantage of the buffer pool to keep frequently accessed data in memory is an important aspect of MySQL tuning. 



COmparing time taken from various stores - in-memory vs ssd


# References

 - [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html)
 - [Making the Buffer Pool Scan Resistant](https://dev.mysql.com/doc/refman/8.0/en/innodb-performance-midpoint_insertion.html)
 - [Latency numbers](https://gist.github.com/hellerbarde/2843375)
 - [Locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference)
 - [InnoDB : Making Buffer Cache Scan Resistant](https://serge.frezefond.com/2009/12/innodb-making-buffer-cache-scan-resistant/)
 - [InnoDB Disk I/O](https://dev.mysql.com/doc/refman/8.0/en/innodb-disk-io.html)