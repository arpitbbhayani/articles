[Partitioning](https://arpitbhayani.me/blogs/partitioning) plays a vital role in scaling a database beyond a certain scale of reads and writes. This essay takes a detailed look into the two common approaches to horizontally partition the data.

# Partitioning

A database is partitioned when we split it, logically or physically, into mutually exclusive segments. Each partition of the database is a subset that can operate as a smaller independent database on its own.

## Our goal with partitioning

Our primary goal with partitioning is to spread the data across multiple nodes, each responsible for only a fraction of the data allowing us to dodge the limitations with vertical scaling. A database is uniformly partitioned across 5 data nodes; each node will be roughly responsible for a fifth of the reads and writes hitting the cluster, allowing us to handle a greater load seamlessly.

## What if partitioning is skewed?

Partitioning does help in handling the scale only when the load spreads uniformly. Partitions are skewed when few (hot) partitions are responsible for bulk data or query load. This happens when the partitioning logic does not respect the data and access pattern of the use-case at hand.

![Skewed Partitioning](https://user-images.githubusercontent.com/4745789/150775353-358b6183-30a2-4fb4-8291-e3642c668747.png)

If the partitioning is skewed, the entire architecture will be less effective on performance and cost. Hence, the access and storage pattern of the use-case is heavily considered while deciding on the partitioning attribute, algorithm, and logic.

# Ways of Partitioning Data

## Range-based Partitioning

One of the most popular ways of partitioning data is by assigning a continuous range of data to each partition, making each partition responsible for the assigned fragment. Every partition, thus, knows its boundaries, making it deterministic to find the partition given the partition key.

![Range-based Partitioning](https://user-images.githubusercontent.com/4745789/150777106-4ee22e27-de48-4dda-999e-f1b286a7d5f5.png)

An example of range-based partitioning is splitting a Key-Value store over 5 partitions with each partition responsible for a fragment, defined as,

```
partition 1: [a - e]
partition 2: [f - k]
partition 3: [l - q]
partition 4: [r - v]
partition 5: [w - z]
```

Each partition is thus responsible for the set of keys starting with a specific character. This allows us to define how our entire key-space will be distributed across all partition nodes.

Given that we partition the data to evenly distribute the load across partition nodes, we create the range of the keys that uniformly distributes the load and not the keyspace. Hence in range-based partition, it is not uncommon to see an uneven distribution of key-space. The goal is to optimize the load distribution and not the keyspace.

### When Range-based partitioning fails?

A classic use-case where range-based partitioning fails is when we range-partition the time-series data on timestamp. For example, we create per-day partitions of data coming in from thousands of IoT sensors.

Since IoT sensors will continue to send the latest data, there will always be just one partition that will have to bear the entire ingestion while others will just be sitting idle. When the write-volume for time-series data is very high, it may not be wise to partition the data on time.

## Hash-based Partitioning

Another popular approach for horizontal partitioning is by hashing the partitioned attribute and determining the partition that will own the record. The hashing function used in partitioning is not cryptographically strong but does a good job evenly distributing values across the given range.

Each partition owns a set of hashes. We hash the partitioned attribute when a record needs to be inserted or looked up. A partition that owns the hash will own and store the record. While fetching the record, we first hash the partition key find the owning partition, and then fire the query to get our record from it.

![Hash-based Partitioning](https://user-images.githubusercontent.com/4745789/150777895-b524d8b2-56f3-4a53-bf8b-27f06b824bc6.png)

Hash-based partitioning defers the problem of hot partition to statistics and relies on the randomness of hash-based distribution. But, there is still a slim chance of some partition being hot when many records get hashed to the same partition; this issue is addressed to some extent with the famous [Consistent Hashing](https://arpitbhayani.me/blogs/consistent-hashing).

### When Hash-based partitioning fails?

Hash-based partitioning is a very common technique of data partitioning and is quite prevalent across databases. Although the method is good, it suffers from a few major problems.

Since the record is partitioned on an attribute through a hash function, it is difficult to perform a range query on the data. Since the data is unordered and scattered across all partitions, we will have to visit all the partitions, making the entire process inefficient to perform a range query on key.

Range queries are doable when the required range lies on one partition. This is something leveraged by [Amazon's DynamoDB](https://aws.amazon.com/dynamodb/) that asks us to specify Partition Key (Hash Key) and Range Key. The data is stored across multiple partitioned and is partitioned by the Hash Key. The records are ordered by Range Key within each partition, allowing us to fire range queries local to one partition.
