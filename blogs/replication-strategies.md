In a distributed system, when replication is set up between data nodes, there are typically three replication strategies - Synchronous, Asynchronous, and Semi-synchronous. Depending on the criticality of data, its consistency, and the use-case at hand, the system chooses to apply one over another. In this essay, we take a quick yet verbose look into these strategies and understand their implications.

Before we jump into the replication strategies, let's first understand the need for them. When the data is replicated, multiple copies of the same data are created and placed on multiple machines (nodes). A system replicates the data to

-   improve availability, or
-   prepare for disaster recovery, or
-   improve performance by leveraging parallel reads across replicated data, or
-   keep the data geographically close to the user, e.g., CDN

The Replication comes into action when the Client initiates the write on the Master node. Once the Master updates its copy of the data, the replication strategy dictates how the data would be replicated across the Replicas.

## Synchronous Replication
In Synchronous Replication, once the Master node updates its own copy of the data, it initiates the write operation on its replicas. Once the Replicas receive the update, they apply the change on their copy of data and then send the confirmation to the Master. Once the Master receives the confirmation from all the Replicas, it responds to the client and completes the operation.

![synchronous replication](https://user-images.githubusercontent.com/4745789/128765459-67347320-5b77-4722-884b-015fc1b0c5fb.png)

If there is more than one Replica in the setup, the Master node can propagate the write sequentially or parallelly. Still, in either case, it will continue to wait until it gets a confirmation, which will continue to keep the client blocked. Thus having a large number of Replicas means a longer block for the Client, affecting its throughput.

Synchronous Replication ensures that the Replicas are always in sync and consistent with the Master; hence, this setup is fault-tolerant by default. Even if the Master crashes, the entire data is still available on the Replicas, so the system can easily promote any one of the Replicas as the new Master and continue to function as usual.

A major disadvantage of this strategy is that the Client and the Master can remain blocked if a Replica becomes non-responsive due to a crash or network partition. Due to the strong consistency check, the Master will continue to block all the writes until the affected Replica becomes available again, thus bringing the entire system to a halt.

## Asynchronous Replication
In Asynchronous Replication, once the Master node updates its own copy of the data, it immediately completes the operation by responding to the Client. It does not wait for the changes to be propagated to the Replicas, thus minimizing the block for the Client and maximizing the throughput.

The Master, after responding to the client, asynchronously propagates the changes to the Replicas, allowing them to catch up eventually. This replication strategy is most common and is the default configuration of most distributed data stores out there.

![asynchronous replication](https://user-images.githubusercontent.com/4745789/128765466-944bf36e-6817-4cf3-9ea4-0ffa724f0d58.png)

The key advantage of using a fully Asynchronous Replication is that the client will be blocked only for the duration that the write happens on the Master, post which the Client can continue to function as before, thus elevating the system's throughput.

One major disadvantage of having a fully Asynchronous Replication is the possibility of data loss. What if the write happened on the Master node, and it crashed before the changes could propagate to any of the Replicas. The changes in data that are not propagated are lost permanently, defeating durability. Although Durability is the most important property of any data store,

Asynchronous Replication is the default strategy for most data stores because it maximizes the throughput. The third type of replication strategy addresses durability without severely affecting throughput, and it is called Semi-synchronous Replication.

## Semi-synchronous Replication
In Semi-synchronous Replication, which sits right between the Synchronous and Asynchronous Replication strategies, once the Master node updates its own copy of the data, it synchronously replicates the data to a subset of Replicas and asynchronously to others.

![semi-synchronous replication](https://user-images.githubusercontent.com/4745789/128833772-d0bbae7d-5e00-4771-90e5-996326affb60.png)

The Semi-synchronous Replication thus addresses the durability of data, in case of Master crash, at the cost of degrading the Client's throughput by a marginal factor.

Most of the distributed data stores available have configurable replication strategies. Depending on the problem at hand and the criticality of the data, we can choose one over the other.
