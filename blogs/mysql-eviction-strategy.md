Disk reads are 4x (for SSD) to 80x (for magnetic disk) [slower](https://gist.github.com/hellerbarde/2843375) as compared to main memory (RAM) reads and hence it becomes extremely important for a database to utilize main memory as much as it can, and be super-performant while keeping its latencies to a bare minimum. Engines cannot simply replace disks with RAM because of volatility and cost, hence it needs to strike a balance between the two - maximize main-memory utilization and minimize the disk access.

The database engine virtually splits the data files into pages. A page is a unit which represents how much data the engine transfers at any one time between the disk (the data files) and the main memory. It is usually a few kilobytes 4KB, 8KB, 16KB, 32KB, etc. and is configurable via engine parameters. Because of its bulky size, a page can hold one or multiple rows of a table depending on how much data is in each row i.e. the length of the row.

# Locality of reference
Database systems exhibit a strong and predictable behaviour called [locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference) which suggests the access pattern of a page and its neighbours.

## Spatial Locality of Reference
The spatial locality of reference suggests if a row is accessed, there is a high probability that the neighbouring rows will be accessed in the near future.

Having a larger page size addresses this situation to some extent. As one page could fit multiple rows, this means when that page is cached in main memory, the engine saves a disk read if the neighbouring rows residing in the same page are accessed.

Another way to address this situation is to [read-ahead](https://dev.mysql.com/doc/refman/8.0/en/innodb-disk-io.html) pages that are very likely to be accessed in the future and keep them available in the main memory. This way if the read-ahead pages are referenced, the engine need to go to the disk to fetch the page, rather it will find the page residing in the main memory and thus saving a bunch of disk reads.

## Temporal Locality of Reference
The temporal locality of reference suggests that if a page is recently accessed, it is very likely that the same page will be accessed again in the near future.

Caching exploits this behaviour by putting every single page accessed from the disk into main-memory (cache). Hence the next time a page which is available in the cache is referenced, the engine need not make a disk read to get the page, rather it could reference it from the cache directly, again saving a disk read.

![Disk cache-control flow](https://user-images.githubusercontent.com/4745789/80286313-4e57e680-8748-11ea-88c2-dcb67f6ac566.png)

Since the cache is very costly, it is magnitude smaller in capacity than the disk. It can only hold some fixed number of pages which means the cache suffers from the problem of getting full very quickly. Once the cache gets full, the engine needs to evict an old page so that the new page, which according to the temporal locality of reference is going to be accessed in the near future, could get a place in the cache.

The most common strategy that decides the page that will be evicted from the cache is the [Least Recently Used cache eviction strategy](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)). This strategy uses Temporal Locality of Reference to the core and hence evicts the page which was not accessed the longest, thus maximizing the time the most-recently accessed pages are held in the cache.

# LRU Cache
The LRU cache holds the items in the order of its last access allowing us to identify which item is not being used the longest. When the cache is full and a newer item needs to make an entry in the cache, the item which is not accessed the longest is evicted and hence the name Least Recently Used.

The one end (head) of the list holds the most-recently referenced page while the fag end (tail) of the list holds the least-recently referenced one. A new page, being most-recently accessed, is always added at the head of the list while the eviction happens at the tail. If a page from the cache is referenced again, it is moved to the head of the list as it is now the most-recently referenced page.

## Implementation
LRU cache is often implemented by pairing a [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) with a [hash map](https://en.wikipedia.org/wiki/Hash_table). The cache is thus just a linked list of pages and the hashmap maps the `page_id` to the node in the linked list, enabling `O(1)` lookups.

![LRU Cache](https://user-images.githubusercontent.com/4745789/80288324-d7751a80-8754-11ea-96ab-6a8e25730bff.png)

## InnoDB's Buffer Pool
MySQL InnoDB's cache is called [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html) which does exactly what has been established earlier. Pseudocode implementation of `get_page` function, using which the engine gets the page for further processing, could be summarized as

```py
def get_page(page_id:int) -> Page:
    # Check if the page is available in the cache
    page = cache.get_page(page_id)

    # if the page is retrieved from the main memory
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
Above caching strategy works wonders and helps the engine be super-performant. [Cache hit ratio](https://www.stix.id.au/wiki/Cache_Hit_Ratio) is usually more than 80% for a mid-sized production-level traffic, which means 80% of the times the page was served from the main-memory (cache) and the engine did not require to make the disk read, and this is a huge deal when we are talking about some heavy concurrent access.

What would happen if an entire table is scanned? - While talking a [dump]((https://dev.mysql.com/doc/refman/8.0/en/mysqldump.html)), or running a `SELECT` without `WHERE` to perform some statistical computations.

Going by the MySQL's aforementioned behaviour, the engine iterates on all the pages and since each page which is accessed not is the most recent one, it puts it at the head of the cache whiles evicting one from the tail. If the table is bigger than the cache, this process will wipe out the entire cache and fill it with the pages of one table. If these pages are not referenced again, this is a total loss and performance of the database takes a hit. The performance of the database will not be back up until these newly added cache pages are evicted from the cache.

# Midpoint Insertion Strategy
MySQL InnoDB Engine ploys an extremely smart solution to solve the notorious problem with Sequential Scans. Instead of keeping its Buffer Pool a pure LRU it tweaks it a little bit.

Instead of treating the Buffer Pool as a huge doubly linked list, it treats it as a combination of two smaller sublists - usually 5/8th and 3/8th of the total size. One sublist holds younger data while the other one holds the older data. The head of the Young sublist holds the most recent pages and the recency decreases as it reaches the tail of the Old sublist.

![MySQL InnoDB Midpoint Insertion Strategy](https://user-images.githubusercontent.com/4745789/80299447-138a9880-87b2-11ea-9b0a-888e0ccf4b49.png)

## Eviction
The tail of the Old Sublist holds the Least Recently Used page and the eviction thus happens as per the LRU Strategy i.e. at the tail of the Old Sublist.

## Insertion
The insertion, instead of happening at head of Young sublist i.e. "newest" end of the list, happens at the head of Old sublist i.e. in the "middle" of the list. This position of the list where the tail of the Young sublist meets the head of the Old sublist is the "midpoint", and hence the name of the strategy is Midpoint Insertion Strategy.

The intent, by inserting in the middle, is that the pages that are only read once, such as during a full table scan, can be aged out of the Buffer Pool sooner than with a strict LRU algorithm.

## Moving from Old sublist to the Young sublist
In any LRU strategy whenever any page from the Buffer Pool (cache) is accessed, it moves to the head of the list. In this strategy as well, whenever the page is accessed, irrespective of its list, it moves to the head of Young sublist.

After the page is in the cache (inserted in the middle), if the page is still in demand and accessed again, it moves to the head of Young sublist and stays in the cache for longer. If after being inserted in the middle the page not accessed at all it continues to stay in the Old sublist until evicted. Since old sublist is shorter, the pages that are not accessed are evicted quicker as compared to a strict LRU implementation.

# References
 - [Buffer Pool](https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html)
 - [Making the Buffer Pool Scan Resistant](https://dev.mysql.com/doc/refman/8.0/en/innodb-performance-midpoint_insertion.html)
 - [Latency numbers](https://gist.github.com/hellerbarde/2843375)
 - [Locality of reference](https://en.wikipedia.org/wiki/Locality_of_reference)
 - [InnoDB : Making Buffer Cache Scan Resistant](https://serge.frezefond.com/2009/12/innodb-making-buffer-cache-scan-resistant/)
 - [InnoDB Disk I/O](https://dev.mysql.com/doc/refman/8.0/en/innodb-disk-io.html)
