In this short essay, we dive deep and understand the "C" in ACID - Consistency.

In this quick read, we will take a detailed look into [Consistency](https://en.wikipedia.org/wiki/Consistency_(database_systems)), understand its importance, functioning, and how the database implements it.

# What is Consistency?

In the context of databases, Consistency is Correctness, which means that under no circumstance will the data lose its correctness.

Database systems allow us to define rules that the data residing in our database are mandated to adhere to. Few handy rules could be

 - balance of an account should never be negative
 - no orphan mapping: there should not be any mapping of a person whose entry from the database is deleted.
 - no orphan comment: there should not be any comment in the database that does not belong to an existing blog.

These rules can be defined on a database using Constraints, [Cascades](https://en.wikipedia.org/wiki/Foreign_key#CASCADE), and Triggers; for example, [Foreign Key constraints](https://en.wikipedia.org/wiki/Foreign_key), [Check constraints](https://en.wikipedia.org/wiki/Check_constraint), On Delete Cascades, On Update Cascades, etc.

![Consistency ACID Database](https://user-images.githubusercontent.com/4745789/124226533-e7417900-db26-11eb-8e88-1c50a9391c44.png)

### Role of the database engine in ensuring Consistency
An ACID-compliant database engine compliant has to ensure that the data residing in the database continues to adhere to all the configured rules. Thus, even while executing thousands of concurrent transactions, the database always moves from one consistent state to another.

### What happens when the database discovers a violation?
Database Engine rollbacks the changes, which ensures that the database is reverted to a previous consistent state.

### What happens when the database does not find any violation?
Database Engine will continue to apply the changes, and once the transaction is marked successful, this state of the database becomes the newer consistent state.

# Why is consistency important?
The answer is very relatable. Would you ever want your account to have a negative balance? No. This is thus defined as a rule that the database engine would have to enforce while applying any change to the data.

# How does the database ensure Consistency?
Integrity constraints are checked when the changes are being applied to the data.

Cascade operations are performed synchronously along with the transaction. This means that the transaction is not complete until the primary set of queries, along with all the eligible cascades, are applied. Most database engines also provide a way to make them asynchronous, allowing us to keep our transactions leaner.

✨ Next up is "I" in ACID - Isolation. Stay tuned.

# References
 - [ACID - Wikipedia](https://en.wikipedia.org/wiki/ACID)
 - [Consistency](https://en.wikipedia.org/wiki/Consistency_(database_systems))
 - [Foreign Key Constraints](https://en.wikipedia.org/wiki/Foreign_key)
 - [ACID Explained - BMC](https://www.bmc.com/blogs/acid-atomic-consistent-isolated-durable/)
 - [ACID properties of transactions](https://www.ibm.com/docs/en/cics-ts/5.4?topic=processing-acid-properties-transactions)
 - [ACID Compliance: What It Means and Why You Should Care](https://mariadb.com/resources/blog/acid-compliance-what-it-means-and-why-you-should-care/)
