Master-Replica architecture is one the most common high-level architectural pattern prevalent in distributed systems. We can find it in use across databases, brokers, and custom-built storage engines. In the previous essay, we saw how a [new replica](https://arpitbhayani.me/blogs/new-replica) is set up in a distributed data store and the challenges that come with that. This essay talks about the worse - nodes going down - impact, recovery, and real-world practices.

# Nodes go down, and it is okay
> Anything that can go wrong will go wrong. - [Murphy's Law](https://en.wikipedia.org/wiki/Murphy%27s_law)

Outages are inevitable; we cannot completely eradicate them, but we can be prepared enough to minimize the impact. One way to make any distributed data store robust is by assuming that the node goes down after executing every operation. Building systems around these aggressive failure scenarios is the easiest way to make any distributed system robust and fault-tolerant.

A few reasons why nodes crash are: system overload, hardware issues, overheating, physical damage, or worse, a natural disaster. Nodes going down is a very common phenomenon, and it happens all the time in massive infrastructures. So, instead of panicking, deal with it by minimizing cascaded failures and speeding up the recovery.

In a Master-Replica setup, there are two kinds of nodes - Master and Replica. Let's see what happens when the nodes start crashing and recover the system after the crash.

# Replica outage

When Replica is down, the reads going to it fail. If the nodes are within an abstracted cluster, the front-facing proxy can redirect the request to another Replica upon discovering the outage.

Talking about writes during the Replica outage, we know that the Replica does not handle any writes directly from the client. Still, it does pull the updates through the [Replication log](https://arpitbhayani.me/blogs/replication-formats) and re-applies the changes on its own copy of data. So, are these writes affected during the outage?

To keep track of the updates that Replica already applied to its data, it keeps track of the [Sequence Number](https://arpitbhayani.me/blogs/new-replica) of the operation. This **sequence number** is stored on disk and is atomically updated after pulling and applying update operation from the Master.

When the Replica crashes and recovers, it reconnects to the Master, and the hindered replication resumes from the last processed sequence number from what was persisted on the disk. Once the replication resumes, the Replica will fetch all the updates that happened on the Master, apply them on its own copy of data, and eventually catch up. 

# Master outage

Master is the most critical component in any distributed data store. When the Master crashes and becomes unavailable, it does not accept any request (read or write) coming to the system. This directly impacts the business, resulting in the loss of new writes coming to the system. 

The 3 typical steps in fixing the Master outage are:

 - Discover the crash
 - Set up the new Master
 - Announce the new Master

## Discovering the crashed Master

The first step of fixing the crashed master is to identify that the Master crashed. This discovery step is not just limited to Master but is also applicable to Replica and other relevant nodes in the datastore. So, although we might use the term "Master" while discovering the crash, the process and the flow would be the same for other nodes.

A typical process of detecting a crash is as simple as checking the **heartbeat** of the Master. This means either Master ping the orchestrator that it is alive or the orchestrator checking with the Master if it is healthy. In both cases, the orchestrator would expect that the Master responds within a certain threshold of time, say 30 seconds; and if the Master does not respond, the orchestrator can infer the crash.

![discovering an outage](https://user-images.githubusercontent.com/4745789/132089584-a5177e7a-3104-4f86-8d9d-cbb106b7ce35.png)

In a typical architecture, the orchestrator is a separate node that keeps an eye on all the nodes and repeatedly checks how they are doing. There are [Failure Detection](https://en.wikipedia.org/wiki/Failure_detector) systems that specialize in detecting failures, and one efficient and interesting algorithm for detecting failure is called [Phi φ Accrual Failure Detection](https://arpitbhayani.me/blogs/phi-accrual) that instead of expecting a heartbeat at regular intervals estimates the probability and sets a dynamic threshold.

## Setting up the new Master

When the Master crashes, there are two common ways of setting up the new Master - manual and automated. Picking one over the other depends on the sophistication and maturity of the organization and the infrastructure. Still, it is typically observed that smaller organizations tend to do it manually, while the larges ones have automation in place.

### The manual way

Once the orchestrator detects the Master crash, it raises the alarm to the infrastructure team. Depending on the severity of the incident and the nature of the issue, the infrastructure engineer will either.

 - reboot the Master node, or
 - restart the Master database process, or
 - promote one of the Replica as the new Master

Setting up the Master after the crash manually is common when the team is lean, and the organization is not operating at a massive infrastructure scale. Master crashing is also once in a blue moon event, and setting up complex automation just for one rare occurrence might not be the best use of the engineer's time.

The entire process is automated once the infrastructure grows massive, and even an outage of a few minutes becomes unacceptable.

### The automated way

In a Master-Replica setup, the automation is mainly around promoting an existing replica as the new Master. So, when the orchestrator detects that the Master crashed, it triggers the [Leader Election](https://en.wikipedia.org/wiki/Leader_election) among the Replicas to elect the new Master. The elected Replica is then promoted, the other Replicas are re-configured to follow this new Master.

![electing the new master](https://user-images.githubusercontent.com/4745789/132089586-d52e558f-10e2-4f10-8807-5920f9117ea8.png)

The new Master is thus ready to accept new incoming writes and reads to the system. This automated way of setting up the new Master is definitely faster, but it requires a lot of sophistication from the infrastructure, the algorithms, and practices before implementation.

## Announcing the new Master

Once the new Master is set up, either manually or elected among the Replicas, this information must be conveyed to the end clients connecting to the Master. So, as the final step of the process, the Clients are re-configured such that they now start sending writes to this new Master.

![announcing the new master](https://user-images.githubusercontent.com/4745789/132089587-dc7e25c6-f43d-4be5-a2c1-e09253ec2205.png)

# The Big Challenge 

What if the Master crashed before propagating the changes to the Replica? In such scenarios, if the Replica is promoted as the new Master, this would result in data loss, or conflicts, or split-brain problems if the old Master continues to act as the Master.

## The Passive Master

Data loss or inconsistencies is unacceptable in the real world, so as the solution to this problem, the Master always has a passive standby node. Every time the write happens on the Master, it is [synchronously replicated](https://arpitbhayani.me/blogs/replication-strategies) to this stand by passive node, and asynchronously to configured Replicas.

The write made on the Master is marked as complete only after the updates are synchronously made on this passive Master. This way, the passive Master node is always in sync with the Master. So when the main Master node crashes, we can safely promote this passive Master instead of an existing Replica.

![The Passive Master](https://user-images.githubusercontent.com/4745789/132282367-50feb0be-f952-4bf3-ab62-85ab4f6c86d6.png)

This approach is far better and accurate than running an election across asynchronously replicated Replicas. Still, it incurs a little extra cost of running a parallel Master that will never serve production traffic. But given that it helps in avoiding data loss, this approach is taken by all managed database services.
