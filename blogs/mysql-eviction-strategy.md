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

## InnoDB's Buffer Pool
MySQL InnoDB's cache is called [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html) which does exactly what has been established earlier. Pseudocode implementation of `get_page` function, using which the engine gets the page for further processing, could be summarized as

```py
def get_page(page_id:int) -> Page:
    # Check if the page is available in the cache
    page = cache.get_page(page_id)

    # if the page is retrieved from the main-memory
    # return the page.
    if page:
        return page

    # retrieve the page from the disk
    page = disk.get_page(page_id)

    # put the page in the cache,
    # if the cache is full, evict a page which is
    # least recently used.
    if cache.is_full():
        cache.evict_page()

    # put the page in the cache
    cache.put_page(page)

    # return the pages
    return page
```

## A notorious problem with Sequential Scans
Above caching strategy works wonders and helps the engine be super-performant. [Cache hit ratio](https://www.stix.id.au/wiki/Cache_Hit_Ratio) is usually more than 80% for a mid-sized production level traffic, which means 80% of the times the page was served from the main-memory (cache) and the engine did not require to make the disk read; and this is a huge deal when we are talking about some heavy concurrent access.

What would happen if an entire table is scanned? - While talking a [dump]((https://dev.mysql.com/doc/refman/8.0/en/mysqldump.html)), or running a `SELECT` without `WHERE` to perform some statistical computations.

Going by the MySQL's aforementioned behaviour, the engine iterates on all the pages and since each page which is accessed not is the most recent one, it puts it at the head of the cache whiles evicting one from the tail. If the table is bigger than the cache, this process will wipe out the entire cache and fill it with the pages of one table. If these pages are not referenced again, this is a total loss and performance of the database takes a hit. The performance of the database will not be back up untill these newly added cache pages are evicted from the cache.

# Midpoint Insertion Strategy
MySQL InnoDB Engine ploys an extremely smart solution to solve the problem with Sequential Scans. Instead of keeping its Buffer Pool a pure LRU it tweaks it a little bit.



"Midpoint insertion strategy" which makes things not a true LRU in order to deprioritize superfluous pages.

but makes exceptions in cases where a page might be read only a single time, such as during a full table scan. This variation of the LRU algorithm is called the midpoint insertion strategy.

```
The technique of initially bringing pages into the InnoDB buffer pool not at the "newest" end of the list, but instead somewhere in the middle. The exact location of this point can vary, based on the setting of the innodb-old-blocks-pct option. The intent is that blocks that are only read once, such as during a full table scan, can be aged out of the buffer pool sooner than with a strict LRU algorithm. 

An acronym for "least recently used", a common method for managing storage areas. The items that have not been used recently are evicted when space is needed to cache newer items. InnoDB uses the LRU mechanism by default to manage the pages within the buffer pool, but makes exceptions in cases where a page might be read only a single time, such as during a full table scan. This variation of the LRU algorithm is called the midpoint insertion strategy. The ways in which the buffer pool management differs from the traditional LRU algorithm is fine-tuned by the options innodb-old-blocks-pct, innodb_old_blocks_time, and the new MariaDB 5.6 options innodb_lru_scan_depth and innodb_flush_neighbors. 
```

# References

 - [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html)
 - [Making the Buffer Pool Scan Resistant](https://dev.mysql.com/doc/refman/8.0/en/innodb-performance-midpoint_insertion.html)
 - [Latency numbers](https://gist.github.com/hellerbarde/2843375)
 - [Locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference)
 - [InnoDB : Making Buffer Cache Scan Resistant](https://serge.frezefond.com/2009/12/innodb-making-buffer-cache-scan-resistant/)
 - [InnoDB Disk I/O](https://dev.mysql.com/doc/refman/8.0/en/innodb-disk-io.html)
