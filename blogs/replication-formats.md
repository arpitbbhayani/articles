[Master-Replica](https://arpitbhayani.me/blogs/master-replica-replication) architecture is one the most common high-level architectural pattern prevalent in distributed systems. We can find it in use across databases, brokers, and custom-built storage engines.

So, when we are employing a Master-Replica pattern to improve availability, throughput, and fault-tolerance, the big question that pops up is how the writes happening on the Master propagates to the Replica. In this essay, we will talk about exactly this and find out about Replication Formats.

# Write Propagation
Once the write operation is successful on the Master node, the changes must be propagated to all the Replicas. This is done via a log known as Replication Log, Commit Log, or Binary Log. Once the write on the Master is successful, an event is recorded in this Log file; and this file is then **pulled** by the Replicas.

Once the Replica gets this log file, it goes through the events and starts applying the necessary changes on its copy of the data. This way, it continuously follows the changes happening on the Master node. The time elapsed between the write operation on the Master and the operation taking effect to the Replica is called Replication Lag.

Now that we have a solid understanding of Write Propagation, we focus on the primary agenda of this essay, Replication Format, and talk about how these formats share the entire Replication process.

# Replication Formats
Any write operation happening on the Master is logged in the Replication log file as an event. The format in which these events are logged in the Log file is called Replication Format. The two Replication formats that are widely used across distributed data stores are Statement-based and Row-based formats.

## Statement-based Format
In Statement-based format, the Master node records the operation as an event in its log, and when the Replica reads this log, it executes the same operation on its copy of data. This way, the operation on the Master node is executed on the Replica, which keeps it in sync with the Master.

Say the Client fires an operation on the Master to bulk update all the `5` tasks of a user to be marked as `done`. The operation fired by the Client on the Master node would look something like this.

```sql
  UPDATE tasks SET is_done = true WHERE user_id = 53;
```

When the write operation is completed on the Master, this exact operation is recorded as an event in the Replication Log file. When the Replica reads this log file, the node executes this operation and updates the same `5` tasks on its own copy of the data.

![statement based replication](https://user-images.githubusercontent.com/4745789/129456634-be745df6-541b-4e75-a1e3-4f4f625cc45e.png)

### Advantages
The events recorded in the Replication Log are the actual operations that happen on the Master. Hence, the log files take up the bare minimum storage space required. It will not matter if the operation affects one row or thousand; it will be recorded as one event in the Log file.

Another great benefit of this format is that it can be used to audit the operations on the database because we are recording the operations verbatim in the Log file.

### Disadvantages
The biggest and the most significant disadvantage of the Statement-based format show up when the non-deterministic operations are fired on the Master. The operations such as `UUID()`, `RAND()`, `NOW()`, etc, generate value depending on factors that are not under our control. When these operations fire on the Replica, they might generate values different from the value they yielded on the Master, leading to data corruption.

Since the Replica node, apart from replicating from the Master, is also actively handling requests, some locks might be taken on some of its entities by the executing queries. When a conflicting query is fired from the replication thread, it could result in unpredictable deadlock or stalls.

## Row-based Format
In Row-based format, the Master node logs the updates on the individual data item instead of the operation. So the entry made in the Log file would indicate how the data has changed on the Master. Hence, when the Replica reads this log, it updates its copy of the data by applying the changes on its data items. This way, the operation on the Master node happens on the Replica, and the Replica nodes remain in sync with the Master.

Say the Client fires an operation on the Master to bulk update all the `5` tasks of a user to be marked as `done`. The operation fired by the Client on the Master node would look something like this.

```sql
  UPDATE tasks SET is_done = true WHERE user_id = 53;
```

In the row-based format, instead of recording the operation, the Master node records the updates made on the data items. Since the operation in question updated `5` rows, the events recorded in the Replication Log file would contain `5` entries, one for each data item changed and would look something similar to

```sql
tasks:121 is_done=true
tasks:142 is_done=true
tasks:643 is_done=true
tasks:713 is_done=true
tasks:862 is_done=true
```

Hence, one operation on the Master is fanned out as series of updates on the data items and is consumed by the Replica. The Replica then reads these events and applies the changes on its copy of the data.

![row based replication](https://user-images.githubusercontent.com/4745789/129456632-ad7b67ae-7ff0-4d35-97b0-0ea6d6a3bd87.png)

### Advantages
The major advantage of the Row-based format is that all the changes can be safely and predictably applied on the Replica. This approach is safe even with the non-deterministic operations because what gets written is the computed value.

### Disadvantages
When the Master node completes the operation, it takes the lock on the Replication Log file and then records the events. Since the number of events recorded in the log file will be the number of data items changed, the lock taken by the Master node will be longer, choking the throughput.

Another obvious disadvantage in this approach is fan-out. If an operation changes 5000 data items, it will result in 5000 events in the Log file, and if such operations are frequent, this will make Logfile take a lot of storage space.
