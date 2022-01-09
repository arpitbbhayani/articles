
Every multi-master replication setup comes with a side-effect - Conflicts. Conflict happens when two or more database accepts conflicting updates on the same record. We say that the updates are conflicting when we cannot resolve them to one value deterministically. In the previous essay, we took a detailed look into [Conflict Detection](https://arpitbhayani.me/blogs/conflict-detection), and in this one, we go in-depth to understand ways to handle conflicts (resolve and avoid).

# Conflict Resolution

In the case of a single-master setup, conflicts are avoided by funneling all the writes sequentially. When there are multiple updates on the same field, the last write operation on the record will determine the final value. We can leverage this insight into devising solutions that apply to multi-master setup.

Given that the writes can hit any Master in a multi-master setup, the challenge is to deterministically find the _order_ of the operations to identify which operation came last. So, the approaches for conflict resolution will all revolve around determining or assigning the order to the operations, somehow.

## Globally unique ID to transaction

One possible way to determine the order of the write operations spanning multiple masters is to assign globally unique monotonically increasing IDs to each write operation. When conflict is detected, the write operation having the largest ID overwrites everything else.

![Globally Unique ID](https://user-images.githubusercontent.com/4745789/148541564-aafe6b1d-66e8-434e-8879-85180d09be8f.png)

A globally unique, monotonically increasing ID generator has challenges and is an exhausting problem to solve for scale across distributed nodes. Still, it is essential to consider the idea behind the solution and understand the pattern.

This approach is similar to ordering write on a single master node but without affecting write throughput and concurrent updates. The monotonically increasing globally unique ID gives an implicit ordering to the writes to determine which one came last and hence mimics *Last Write Wins*.

## Precedence of a database

Given that managing an ID generator at scale could be taxing, another possible solution is to assign the order to the master nodes. Upon conflict, the write from the Master having the highest number wins.

![Database Precedence - Conflict Resolution](https://user-images.githubusercontent.com/4745789/148541568-7f1da590-62ad-4764-9995-a3569fc23e0a.png)

This approach is very lightweight, given that assigning orders to master nodes is simple and an infrequent activity. This approach will not guarantee the actual ordering of writes, so it is possible that the actual Last Write got overwritten by some write that happened on Master with the higher ID (precedence).

## Track and Resolve

If, for a use case, it is not possible to resolve the conflicts at the database level, then the best approach in such a scenario is to record the conflict in a data structure designed to preserve all the information. Build a separate job that reads this data structure and resolves the conflict through a custom business logic.

# When to resolve conflict?

There are two possible places where we can inject our conflict resolution logic (handler); the first one is upon writing, and the second one is upon reading.

## On Write

In this approach, as soon as a conflict is detected, the custom conflict resolution logic has triggered that resolve the conflict and make the data consistent. This is a more proactive approach to conflict resolution.

## On Reading

The other approach is to be lazy and resolve conflict when someone tries to read the conflicting data. The custom conflict resolution handler is triggered when the read is triggered on the conflicting data, the database engine realizing it and then invoking the solution handler.

This lazy approach can be seen in action in scenarios where we have to ensure that the [writes are never rejected](https://arpitbhayani.me/blogs/conflict-detection), no matter what.

# Conflict Avoidance

Now that we have gone through these seemingly complex ways of conflict resolution, it seems better to try to avoid conflicts in the first place. This is indeed the simplest and widely adopted strategy for dealing with conflicts.

A possible way to avoid conflict is by adding stickiness in the system, allowing all writes of a particular record to go to a specific Master node, ensuring sequential operations, and simplifying the core requirement of *Last Write Wins*.
