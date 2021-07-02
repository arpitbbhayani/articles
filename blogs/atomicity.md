In this short essay, we dive deep and understand the "A" of ACID - Atomicity.

In this quick read, we will take a detailed look into [Atomicity](https://en.wikipedia.org/wiki/Atomicity_(database_systems)), understand its importance, and learn about implementing it at various levels.

# What is atomicity?

A single database transaction often contains multiple statements to be executed on the database. In Relational Databases, these are usually multiple SQL statements, while in the case of non-Relational Databases, these could be multiple database commands.

Atomicity in ACID mandates that each transaction should be treated as a single unit of execution, which means either all the statements/commands of that transaction are executed, or none of them are.

At the end of the successful transaction or after a failure while applying the transaction, the database should never be in a state where only a subset of statements/commands is applied.

An atomic system thus guarantees atomicity in every situation, including successful completion of transactions or after power failures, errors, and crashes.

![Atomicity ACID](https://user-images.githubusercontent.com/4745789/124223798-0e497c00-db22-11eb-868d-8faefc44361c.png)

A great example of seeing why it is critical to have atomicity is Money Transfers.

Imagine transferring money from bank account A to B. The transaction involves subtracting balance from A and adding balance to B. If any of these changes are partially applied to the database, it will lead to money either not debited or credited, depending on when it failed.

# How is atomicity implemented?

## Atomicity in Databases
Most databases implement Atomicty using logging; the engine logs all the changes and notes when the transaction started and finished. Depending on the final state of the transactions, the changes are either applied or dropped.

Atomicity can also be implemented by keeping a copy of the data before starting the transaction and using it during rollbacks.

## Atomicity in File Systems
At the file system level, atomicity is attained by atomically opening and locking the file using system calls: open and flock. We can choose to lock the file in either Shared or Exclusive mode.

## Atomicity at Hardware Level
At the hardware level, atomicity is implemented through instructions such as Test-and-set, Fetch-and-add, Compare-and-swap.

## Atomicity in Business Logic
The construct of atomicity can be implemented at a high-level language or business logic by burrowing the concept of atomic instructions; for example, you can use compare and swap to update the value of a variable shared across threads concurrently.

Atomicity is not just restricted to Databases; it is a notion that can be applied to any system out there.

✨ Next up is "C" in ACID - Consistency. Stay tuned.

# References
 - [ACID - Wikipedia](https://en.wikipedia.org/wiki/ACID)
 - [Atomicity - Wikipedia](https://en.wikipedia.org/wiki/Atomicity_(database_systems))
 - [ACID Explained - BMC](https://www.bmc.com/blogs/acid-atomic-consistent-isolated-durable/)
 - [ACID properties of transactions](https://www.ibm.com/docs/en/cics-ts/5.4?topic=processing-acid-properties-transactions)
 - [ACID Compliance: What It Means and Why You Should Care](https://mariadb.com/resources/blog/acid-compliance-what-it-means-and-why-you-should-care/)
