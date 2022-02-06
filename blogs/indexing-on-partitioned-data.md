The previous essay looked at two popular ways to [horizontally partition](https://arpitbhayani.me/blogs/data-partitioning-strategies) the data - Range-based Partitioning and Hash-based Partitioning. In this essay, we will take a detailed look into how we could [index](https://en.wikipedia.org/wiki/Database_index) the partitioned data, allowing us to query the data on secondary attributes quickly.

# Partitioning and Querying

In a [partitioned database](https://arpitbhayani.me/blogs/data-partitioning), the data is split horizontally on the partitioned key. Given that each partition is required to handle a fragment of data, the query that is bound to a single partition is answered very quickly vs the query that requires cross partition execution. But what happens when we want to query the data on any attribute other than the partitioned key; that is where things become very interesting.

Say we have a `movies` collection partitioned on `id` (the movie ID), and each record has the following structure.

```json
{
	"id": tt0111161,
	"name": "The Shawshank Redemption",
	"genre": ["Drama"],
	"year": 1994
}
```

Given that the collection is partitioned on `id`, querying a movie by its `id` will be lightning-quick as it would need to hit just one partition to grab the record as determined by the Hash function.

![Pointed Query in Partitioned Database](https://user-images.githubusercontent.com/4745789/152688735-16e15acf-fcee-491c-9b74-965e3590df9c.png)

What if we need to get the list of all the movies belonging to a particular genre? Answering this query is very expensive as we would have to go through every record across all the partitions and see which ones match our criteria, accumulate them, and return them as the response. Given that this process is tedious we leverage indexing to compute the answer quickly.

# Indexing

Indexing is a popular technique to make reads super-efficient, and it does so by creating a query-able mapping between indexed attributes and the identity of the document. An index that maps non-primary key attributes to the record id is called a Secondary Index.

Say, we have the following 6 movie documents, partitioned on `id` (the movie ID) and split across 2 partitions as shown below

```json
{ "id": tt0111161, "name": "The Shawshank Redemption", "genre": ["Drama"], "year": 1994 }
{ "id": tt0068646, "name": "The Godfather", "genre": ["Crime", "Drama"], "year": 1972 }
{ "id": tt0071562, "name": "The Godfather: Part II", "genre": ["Crime", "Drama"], "year": 1974 }


{ "id": tt0468569, "name": "The Dark Knight", "genre": ["Action", "Crime", "Drama"], "year": 2008 }
{ "id": tt0050083, "name": "12 Angry Men", "genre": ["Crime", "Drama"], "year": 1957 }
{ "id": tt0108052, "name": "Schindler's List", "genre": ["Biography", "Drama", "History"], "year": 1993 }
```

![movies Partitioned across 2 partitions](https://user-images.githubusercontent.com/4745789/152688989-d70c541f-92c9-4f3f-ad54-740f660f7bd0.png)

To query movies by `genre = Crime`, we will have to index the data on `genre` allowing us to find the relevant documents quickly. Indexes are a little tricky in a partitioned database, and there are two ways to implement them: Local Indexing and Global Indexing. [AWS's DynamoDB](https://aws.amazon.com/dynamodb/) is a partitioned KV store that supports secondary indexes on non-partitioned attributes, and it supports both of these indexing techniques.

## Local Secondary Index

Local Secondary Indexing creates indexes on a non-partitioned attribute on the data belonging to the partition. Thus, each partition has a secondary index that is built on that data owned by that partition and it knows nothing about the data present in other partitions. Hence, on the example that we have at hand, the Local Secondary Index on attribute `genre` would look like this

![Local Secondary Index - Movies](https://user-images.githubusercontent.com/4745789/152689634-c3235f38-5cf2-4446-af87-ecd58807296d.png)

The key advantage of having a Local Secondary Index is that whenever a write happens on a partition, the index update happens locally without needing any cross partition communication (mostly a network IO). When the data is fetched from a Local Secondary Index, it is fetched from the partition that holds the index data and the entire record; so execution takes a minimal time.

Local Secondary Indexes come in handy when we want to query the data in conjunction with the partitioned key. For example, if the movies were partitioned by `genre` (instead of `id`) and we create an index on `year` it will help us efficiently answer the queries like movies of a particular `genre` released in a specific `year`.

### When Local Secondary Indexes suffer?

Although Local Secondary Indexes are great, they cannot efficiently answer the queries that require cross partition fetch. For example, if we fire the query to get all `Crime` movies through a Local Secondary Index, we will be getting the records that are local to the partition on which the query executes.

But, answering the query to fetch all the movies from the `Crime` genre requires us to go through all the partitions and individually execute the query, then gather (accumulate) the results and return. This is an extremely expensive process that is also prone to network delays, partitioning, and unreliability.

![Scatter Gather Local Secondary Index](https://user-images.githubusercontent.com/4745789/152691045-f9958236-b532-4fed-a5d3-902962edd1b0.png)

We face this limitation because the movies with the `crime` genre are distributed across partitions because there is no way to ensure all movies with the `Crime` genre belong to the same partition when the data partitioning is done on `id`.

Hence, it is very important to structure data partitioning and indexing depending on the queries we want to support ensuring that the queries can be answered through just one partition. To address this problem of being able to query the data on an indexed attribute, we create Global Secondary Indexes.

## Global Secondary Index

Global Secondary Indexes choose not to be local to a partition's data instead, this indexing technique covers the entire dataset. Global Secondary Index is a kind of re-partitioning of data on a different partition key allowing us to have faster reads and a global view on the indexed attribute.

On the example that we have at hand, Global Secondary Index on `genre` would look like this.

![Global Secondary Index - Movies example](https://user-images.githubusercontent.com/4745789/152696486-33d94f29-6918-48f6-8644-b6ee809a2a81.png)

The key advantage of having a Global Secondary Index is that it allows us to query the data on the indexed attribute globally and not limit ourselves to a fragment of the data. Since it literally re-partitions the data on a different attribute, firing query on the indexed attribute requires it to hit just one partition for execution and thus saving fanning out to multiple partitions.

### When Global Secondary Indexes suffer?

The database takes a performance hit when a Global Secondary Index needs to be synchronously updated as soon as the update happened on the main record, and if the updation happens asynchronously then the readers need to be aware of a possible stale data fetch.

Synchronous updation of a Global Secondary Index is an extremely expensive operation given that every write on primary data will be translated to a number of synchronous updation across partitions for index updation wrapped in a long [Distributed Transaction](https://en.wikipedia.org/wiki/Distributed_transaction) to ensure [Data Consistency](https://en.wikipedia.org/wiki/Data_consistency).

![Global Secondary Index updation](https://user-images.githubusercontent.com/4745789/152697444-4b90d88b-fa18-4456-b8ba-bdde15ddbac4.png)

Hence, in practice, most Global Secondary Indexes are updated asynchronously involving a rick of Replication Lag and stale data reads. The readers from these indexes should be okay with reading stale data and the system being eventually consistent. The delay in propagation could vary from a second to a few minutes, depending on the underlying hardware's CPU consumption and network capacity.
