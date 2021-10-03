Asynchronous replication leads to a fascinating situation where it feels like we are going through a wormhole traveling back and forth in time. In this essay, we understand why this happens and the consequences and devise a quick solution to address it.

# Through the wormhole

As per Wikipedia, a [wormhole](https://en.wikipedia.org/wiki/Wormhole) can be visualized as a tunnel with two ends at different points in spacetime (i.e., different locations, different points in time, or both), allowing us to traverse back and forth in time again and again. So, where exactly is a wormhole in the context of a distributed datastore?

Say, we have a distributed KV store having one Master and 2 Replica nodes, and we make three updates on a key `X`, the first update `U1` sets `X` as `1`, the second update `U2` sets it to `2`, while the third update `U3` sets `X` to `3`. Like in a typical Master Replica setup, the writes go to the Master, and they are propagated to Replicas through an Asynchronous replication. The reads are typically sent to any one of the Replicas at random.

The writes are propagated to the Replicas [asynchronously](https://arpitbhayani.me/blogs/replication-strategies), which means both the Replicas will have slight replication lags and say this lag on Replica 1 is of `2 seconds`, and on Replica 2 is `1 second`. As of current time instant, all the three updates `U1`, `U2`, and `U3` have happened on the Master, while only update `U1` has reached Replica 1, and it is lagging behind Replica 2 that saw updates `U1` and `U2`.

![time traveling database - monotonic reads](https://user-images.githubusercontent.com/4745789/135746302-4ff940ba-9ca4-4925-9362-d5fc03f166f6.png)

Say, after making the update `U3` at instant `t`, the User initiates a read that hits Replica 2. Since the update `U3` is yet to reach the Replica 2, it returned `2`, an old value of `X`. This breaks [Read your write consistency](https://arpitbhayani.me/blogs/read-your-write-consistency) and make the user feel that the recent write is lost. Say the user makes another read after this one, which now reaches Replica 1, and since the Replica 1 has just seen the update `U1`, it returns the value `1`, which is even older than the last returned value.

Here we see that after the latest write `U3`, the two successive reads yielded historical values depending on which Replica it hit, giving a feel of traveling back in time. The situation becomes even more interesting when the Replica starts to catch up. Depending on which Replica the read request went to, the User would be oscilating between the old and new values of `X`, giving it a feel of going through the wormhole.

# Monotonic Reads

Monotonic read guarantees users to see value always moving forward in time, no matter how many or how quickly it tries to read the data. It is a weaker guarantee than strong consistency but a stronger one than eventual consistency.

## Achieving Monotonic Reads

The root cause of this seemingly random fetch lies in allowing the read request to hit Replicas with different Replication Lags. For a particular Replica, the writes are always applied in order, moving forward in time. So, a niche solution for this problem is to make the read request of a user sticky to a replica.

![monotonic reads](https://user-images.githubusercontent.com/4745789/135746307-2c3fc584-7154-4d13-96d9-b1a2b29c7d49.png)

Once it is ensured that a particular user's request only goes to a specific replica, that User will see updates always moving forward in time as the Replica continues to catch up with the Master.

To implement stickiness, the server can pick the Replica using the [hash](https://en.wikipedia.org/wiki/Hash_function) of the User ID instead of picking it randomly. This way, the stickiness between a user and a Replica helping us achieve Monotonic Reads.
