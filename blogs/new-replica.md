A distributed data store adds Replica to scale their reads and improve availability. This is the most common and logical way to scale the throughput of a system without massively changing the architecture. In the previous essays, we talked about [Master-Replica Replication](https://arpitbhayani.me/blogs/master-replica-replication), different [Replication Strategies](https://arpitbhayani.me/blogs/replication-strategies), and [Replication Formats](https://arpitbhayani.me/blogs/replication-formats). In this one, we take a look into how these Replicas are set up and understand some quirky nuances.

# Setting up a Replica

In the [Master-Replica setup](https://arpitbhayani.me/blogs/master-replica-replication), Replica is a node that follows the Master. The updates happening on the Master are communicated to the Replica through the process called Replication. The Master publishes the updates on the Replication Log, which are then pulled by the Replica and applied on its own copy of data.

The Replica nodes are read-only in the Master-Replica setup, making this architecture pattern suitable for scale reads and improving availability. The most typical steps taken when a new Replica is set up are

1.  Take a point-in-time **snapshot** of the Master data.
2.  **Spin up** a Replica node with this snapshot.
3.  **Start** the process on the Replica and configure it to follow the Master.
4.  The process of **Replication** begins, and the Replica eventually **catches up**.

![The new Replica](https://user-images.githubusercontent.com/4745789/130204028-db759df1-2ea9-4aa5-98f4-6cb3e2b16813.png)

Now that we have talked about the general process of setting up a new Replica, let's dissect the steps and answer really quirky questions about it.

## Replica keeping track of Replication

Once the Replication is set up between the Replica and the Master, one of the key things to understand is how a Replica keeps track of operations and updates that it has pulled and applied on its own copy of data.

The idea to achieve this is simple. Every update on the Master is associated with a monotonically increasing **sequence number**. Both the Master and the Replica keep track of this sequence number, and it denotes the sequence number of the last operation executed on their respective copy of the data.

Since the Master generates the sequence number, it holds the latest one. The Replica could be a couple of sequence numbers behind, as it needs to pull the updates from the Master, apply the updates, and then update the sequence number. Thus, by tracking the sequence number, the Replica keeps track of the Replication, order of the updates, and understands the Replication lag.

![Sequence Number: Replica](https://user-images.githubusercontent.com/4745789/130345784-8892f5f4-7ed1-4588-bbac-08ce39b7c752.png)

Since the Replica persists the sequence number on disk, even if the server reboots, it can continue to resume the Replication since the reboot.

## Why do we need a point-in-time snapshot?

Now that we know how a Replica keeps track of the replication, we answer an interesting question; do we really need a point-in-time snapshot of Master to create a Replica?

The answer to this situation is simple; it is not mandatory to take a point-in-time snapshot of Master and create Replica out of it. We can also do it on a blank data node with no hiccups at all. The only caveat here is that when we set up Replication on a blank data node, it will have to pull in all the update operations on the Master node and apply them to its own copy of the data.

When a Replica needs to pull in literally every single update operation and apply, it will take a far longer time to catch up with the Master. The Replica will start with an extremely high Replica lag, but eventually, this lag will reduce. Nonetheless, it will take a lot of time to catch the Master, rendering this approach unsuitable.

When the point-in-time snapshot is taken, the sequence number of the Master, at that instant, is also captured. This way, when the Replication is set up on this copy of data, it will have far fewer operations to replicate before it catches up with the Master. Hence, instead of creating Replica from scratch, setting it up from a recent point-in-time snapshot of Master makes the Replica quickly catch up with the Master.

## How does a Replica catch up with the Master?

Replica pulls the replication log from the Master node and applies the changes on its own copy of data. If Replica is already serving live read requests, how it actually catches up with the Master?

The entire Replication process is run by a separate Replication thread that pulls the data from the Replication Log of the Master and applies the updates on its own copy of the data. For Replication to happen, the thread needs to be scheduled on the CPU. The more CPU this Replication thread gets, the faster the replication would happen. This is how the Replica continues to Replicate the updates from the Master while serving the live traffic.

## Is it possible for a Replica never to catch the Master?

If the progress of Replication depends on the CPU cycles that the Replication thread gets, does this mean it is possible for a Replica never to catch the Master?

Yes. It is very much possible for a replica to never catch up with the Master. Since the Replica typically also serves the live read traffic, if some queries are CPU intensive or take massive locks on the tables, there are chances that the Replication thread might get a minimal CPU to continue to replication.

Another popular reason a Replica might never catch up with the Master is when the Master is overwhelmed with many write operations. The influx of write is more than what Replica can process, leading to an ever-increasing Replica lag.

Hence whenever a Replica sees a big enough Replica lag, the remediation is

-   to kill read queries that are waiting for a long time, or
-   to not let it serve any live traffic for some time, or
-   to kill CPU intensive read queries, or
-   to kill queries that have taken locks on critical data

We ensure that the Replication thread gets CPU that it deserves to continue the replication by taking some or all of the above actions. Our intention while fighting high replica lag is to reduce somehow the load on the CPU, whatever it takes.
