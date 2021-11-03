
A not-so-common yet super-useful replication strategy is Multi-Master replication - in which multiple nodes in the cluster accept writes, contrary to what is observed in a typical [Master-Replica replication](https://arpitbhayani.me/blogs/master-replica-replication). In this essay, we look at what Multi-Master Replication is, the core challenge it addresses, use-cases we can find this replication in action, and the possible concerns of using it.

# Multi-Master Replication

A Multi-Master setup has multiple nodes of a database cluster accepting the write requests. It typically depends on the client to pick a Master node, or an abstracted proxy may choose one. As soon as a Master node gets the write request, it accepts it and applies the changes. Once the update is made on one Master, it is [propagated](https://arpitbhayani.me/blogs/replication-strategies) to all other Master nodes of the cluster asynchronously, making the data eventually consistent.

Each Master, thus, also acts as a replica (not read-replica) for the other Masters, reading and applying the updates on its copy of data. Each Master node can optionally form a sub-cluster by adding [read-replicas](https://arpitbhayani.me/blogs/master-replica-replication) and scaling the overall incoming reads.

![Multi-Master Replication](https://user-images.githubusercontent.com/4745789/139211714-fc9266bd-ca22-48c4-9095-c6bff0ae99e6.png)

# Why do we need a Multi-Master setup?

An exciting exploration is to find why we would ever need a Multi-Master setup and what kind of problem it would solve for us? Here are three key reasons to have a Multi-Master setup.

## Sharing Load

The most common reason to have a Multi-Master setup is to allow our database cluster to handle more write traffic than a single node. Vertical scaling has theoretical and practical limitations, and the machine can’t go beyond a particular scale.

To truly scale the database cluster, we have to scale the reads by adding read-replicas and having multiple machines that handle writes. Hence, when the writes on a database cluster become a bottleneck, have multiple Master nodes instead of a single one that can take in incoming writes allowing our cluster to share the load and handle multi-fold of write requests.

Typically, clients choose one of the many Master nodes to send their Write requests. These updates are then propagated [asynchronously](https://arpitbhayani.me/blogs/replication-strategies) to other Masters keeping them in sync with the changes and making the system eventually consistent.

## Maintaining a second copy

The second common scenario where Multi-Master comes in handy is when we want to keep a second consistent copy of our Master database, which is also required to accept the write requests. This sounds convoluted, but in the real world, such a requirement is widespread. Let’s go through a few scenarios.

### No SPoF Master

Just like any other node in the database cluster, the Master node can also crash. If the only Master node of the cluster takes all the write requests, crashes, it makes the entire ineffective resulting in a massive downtime. This is a classical case of our Master node becoming the [Single Point of Failure](https://en.wikipedia.org/wiki/Single_point_of_failure).

Given that the failures and crashes are inevitable, it makes sense to have multiple masters running in a cluster and all of them entertaining the write requests. This way, if one of the Master nodes crashes, the other Master can continue to handle the write requests seamlessly, and the cluster will continue to function.

### Lower latencies across geographies

When the clients of your database are spread across geographies, the write latencies shoot up since all the writes across all geographies have to go to this one region where the Master resides.

To keep the write latencies to a minimum across geographies, we set up Multi-Master such that one Master node resides in one region closer to the user. When a client makes the write request, the request can be served from the closest Master giving a great user experience.

### Upgrading the database to a newer version

Every database needs at least a yearly upgrade, and it is never easy to do it on the fly. Before the version is upgraded, every dependent service typically tests its business logic on a newer version. We need to have two databases running during this exercise - one with the older version handling production and the other with the newer version. Both of these databases require to be kept in sync, and both should accept writes. The writes on the newer database will not be as dense as on the production, considering that the service teams will test their workflows on it.

A typical way to facilitate this parallel setup is to have a Multi-Master replication set up between the two databases - one with an older version serving production traffic, the other with a newer version given to application teams to test their workflows. Apart from testing their workflows, the parallel setup also helps incrementally move traffic from old to new versions keeping the blast radius at a bare minimum in case of failure.

The other two similar scenarios where Multi-Master replication comes in handy and are very similar to database upgrade are

-   Encrypting the database without taking in a significant downtime
-   Downscaling an over-provisioned database without a massive downtime
    

## Need of a split-brain

The third but particular reason for a Multi-Master setup is where having a split-brain is the necessity and the core of the system. In a general sense, split-brain is considered an erroneous situation that causes mayhem, but it is not a bug but a feature in these scenarios.

A great example of such a system is Collaborative Editing tools like Google Docs, where multiple users on the same document are editing it simultaneously. Each user has its copy of data and edits as if it owns the document wholly. Another example of a split-brain use case has multiple clients using an offline database to work on the same set of values offline and then sync them with a central value store once the internet is back.

# Concerns with Multi-Master

Although Multi-Master replication is excellent and solves a wide range of problems in the real world, it comes with its own set of concerns. Before deciding if you want to have a Multi-Master setup, do consider the following concerns.

## Eventual Consistency

With the replication between Multi-Master being asynchronous, the updates made on one Master will take some time to reflect on the other Masters, making the system eventually consistent. Because of this eventual consistency, a relational database running in Multi-Master mode will lose its ACID guarantees.

## Sluggish Performance

Every update happening on one Master needs to be sent to every other Master node in the cluster. This data movement adds a considerable load on the network bandwidth and could lead to a sluggish network performance at scale.

## Conflict Resolution

The main concern while running a database in Multi-Master mode is Conflict. Since all Master nodes accept writes, there may arise situations where the same entity is updated on multiple Master simultaneously, leading to conflicts while syncing. The way these conflicts are handled depends on the application at hand. Some use cases would suggest discarding the entire sequence of writes, while others would mean the last write wins. It becomes the responsibility of the business logic and the use case to define steps to be taken upon a conflict.
