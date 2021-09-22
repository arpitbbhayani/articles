The most common way to scale the reads hitting a distributed data store is by adding [Read Replicas](https://arpitbhayani.me/blogs/master-replica-replication). These replicas handle all the reads of the systems freeing up the Master to deal with the writes. Although Replicas do help us scale, it brings a new set of problems; and in this essay, we discuss one such issue, called "Read-your-write" consistency, and look at possible solutions.

# The Problem

In a [Master-Replica](https://arpitbhayani.me/blogs/master-replica-replication) setup, the Writes happening on the Master take some time to reach the Replica. This dealay in propagation is called Replication Lag. If a client has made a Write and is immediately trying to read the written item, this read may go to the Read Replica that is yet to sync with the Master.

When the client issues the Read on a Replica that has yet to receive the write, it leads to an undesirable behavior wherein the client will see the old value (or null) and think that the write it made was lost.

**Read-Your-Writes consistency** states that the system guarantees that, once an item has been updated, any attempt to read the record by the same client will return the updated value. This consistency makes no promises about other clients getting the updated value immediately after the Write and is meant to reassure the user that their Write is successful.

## Problem in action

To ensure that the issue we are trying to address is not something made up, let's see what happens across industries when we do not ensure Read-your-write consistency.

Imagine you made a post on a Social Platform, and when you refreshed the page, it threw a 404 error saying Post does not exist, or when you fixed a spelling mistake on the post and refreshed the page, you still see the old text with the same spelling mistake. This inconsistency leads to a terrible user experience.

![Read after Write Fails - Read Your Write Consistency](https://user-images.githubusercontent.com/4745789/134198510-78129b65-5c4c-4d88-a10a-39523d1886d7.png)

In some cases, caching is the root cause; but it is also possible that the Read request for the post was routed to the Read Replica, which was yet to apply the write that happened on the Master, typically due to Replication Lag.

A few more examples of why we need Read-Your-Write consistency:
 - Imagine getting a match on Tinder and disappearing upon refresh
 - Imagine buying an AAPL Stock and seeing no trace of it on the orders page
 - Imagine adding items in your Amazon cart and realizing it empty when placing the order

# Implementing Read-your-write consistency

The primary root cause of not having Read-your-write consistency is Replication Lag. The longer it takes for the write to propagate to the Replica, the longer our end user will see an inconsistent behavior depending on which Read Replica serves the read. So, every single solution revolves all-around reading from a place where Replication Lag is zero. We start dissecting and devising approaches to address this problem.

## Synchronous Replication

Replication Lag exists because the writes are propagated to Replica [asynchronously](https://arpitbhayani.me/blogs/replication-strategies). If the replication is done synchronously, every Write operation on Master is not termed completed unless it is done replicating it on all the Replicas. This way, the Master and the Replica will always remain in sync with ZERO Replication Lag, and no matter to which Replica the read is forwarded, it will always have the latest copy of the data.

![Synchronous Replication - Read Your Write Consistency](https://user-images.githubusercontent.com/4745789/128765459-67347320-5b77-4722-884b-015fc1b0c5fb.png)

Synchronous Replication sounds tempting and foolproof approach, but it comes at a massive cost. Synchronous Replication severely affects the write throughput of the database. More than that, write failing on any one of the Replica will choke the entire system. Gaining such Strong Consistency at the expense of write throughput and availability is not a great choice.

## Pinning User to Master

Instead of serving Read requests from the Replica, what if we also serve them from the Master. Forwarding all the read requests to Master defeats the purpose of creating Read Replica - scaling reads. But since we know that the Master will always have the latest copy of the data, can we devise something around it?

Instead of routing all the reads from all the users to the Master, what if we routed reads of the User who recently performed the Write to the Master? This sounds promising and addresses our concern, and this exactly is Pinning the User to the Master.

When a user performs a Write operation, for a specific time window, we pin the User to the Master node, which means every single Read and Write coming from the user will go to the Master, which means the Reads will happen from the data node that always has the latest copy of the data and hence we would achieve Read-your-write consistency.

The time window for pinning should be big enough to ensure that the Writes happened on the Master would have propagated to all the Replicas; this ensures that once the pinning window is over and reads of the user start hitting the Replica, it would continue access the latest copy of the data.

![User PInning to Master - Read Your Write Consistency](https://user-images.githubusercontent.com/4745789/134198508-4c8bd1e4-2336-4063-8ceb-06e675c24554.png)

Although this solves the problem well, it is not optimal when the system is very write-heavy. If in a system most users Write, this would mean the requests most users will go to the Master, most of the time, defeating the purpose of Replica and becoming the bottleneck. 

## Fragmented Pinning

Pinning a user to the Master would mean queries, both Read and Write, made by the user will hit the Master for a configured time window. But instead of pinning everything, what if we pick only a few critical reads to hit the Master; this is Fragmented Pinning.

For example, in social media, once the user made or updated a post, pin the user to the Master for 10 minutes such that the request for getting the post goes to the Master; all other reads would continue to hit the Replica.

![Fragmented Pinning - Read Your Write Consistency](https://user-images.githubusercontent.com/4745789/134198504-5b886713-9a16-45ba-9a63-332d19b5894c.png)

By doing fragmented pinning, we ensure that most critical and most likely Read operations, during the pinned window, go to the Master, ensuring that our Master is not overwhelmed even when the system is write-heavy.

## Master Fallback

There is one more way of ensuring Read-your-write consistency, but it works well for a system with a lower Replication Lag, and most queries made on the data store are for keys that exist, i.e., fewer 404s, and the approach is using Master as a fallback.

![Master Fallback - Read Your Write Consistency](https://user-images.githubusercontent.com/4745789/134198497-099bce25-bef1-468e-84b2-69b31e1ae3e0.png)

There is no User Pinning in this approach, and all the Read operations go to the Replica while the Master node only handles Write. The Master and Replica are kept in sync using [asynchronous replication](https://arpitbhayani.me/blogs/replication-strategies). If the Read request that went to the Replica resulted in the 404, i.e., Key Not Found, the application forwards the same query on the Master node and then returns the response.

Since the reads go to the Replica and the Master every time the data is not present in Replica, for this system to be efficient, we need fewer cases where this particular path would be taken, and also the Replication Lag to not inflate much.
