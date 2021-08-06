Master-Replica architecture is one the most common high-level architectural pattern prevalent in distributed systems. We can find it in use across databases, brokers, and custom-built storage engines. In this essay, we talk about everything we should know about the Master-Replica replication pattern.

A system that adheres to the Master-Replica replication architecture contains multiple nodes and each node, called Replica, holds an identical copy of the entire data. Thus if there are N nodes in the system, there will be N copies of the data.

![Master-Replica Replication](https://user-images.githubusercontent.com/4745789/128564165-92d3413a-a329-4456-b055-177ed83e989a.png)

# Scaling Reads

With  N nodes capable of serving the data, we easily scale up the reads by a  factor of N. Hence, this pattern is commonly put in place to amplify and scale the reads that the system can handle.

# Handling Writes

With  N nodes that hold and own the data, the writes become tricky to handle.  In the Master-Replica setup, the writes go to one of the pre-decided nodes that act as the Master. This Master node is responsible for taking up all the writes that happen in the system.

Master is not any special node; rather, it is just one of the Replicas with this added responsibility. Thus in the system of N nodes, 1 node is the Master that takes in all the writes, while the other N - 1 node caters to the read requests coming from the clients.

# Write Propagation

Once the write operation is successful on the Master node, the changes are propagated to all the Replicas through Replication Log (Commit Log, Bin  Log, etc.), letting the system eventually catch up.

The time elapsed between the write operation on the Master and the operation propagating to the Replica is called Replication Lag. This is one of the core metrics that is observed 100% of the time.

# What happens when the Master goes down?

Since the Master node takes in all the write operations, it going down is a  massive event. The write operation that happens when the Master is facing an outage results in an error.

When the system detects such an outage, it tries to auto-recover by promoting one active Replica as the new Master by running a Leader Election algorithm. All the healthy Replicas participate in this election and, through a consensus,  decide the new Master.

Once the new Master is elected, the system starts accepting and processing the writes again.

# Master-Replica in action

This is a widespread pattern that we can find across almost all the databases and distributed systems. Some of the most common examples are:

 - Relational databases like MySQL, PostgreSQL, Oracle, etc.
 - Non-relational databases like MongoDB, Redis, etc.
 - Distributed brokers like Kafka, etc.  
