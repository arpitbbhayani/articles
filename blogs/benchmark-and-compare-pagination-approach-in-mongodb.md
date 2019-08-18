[MongoDB](https://www.mongodb.com/) is a document based data store and hence pagination is one of the most common use case of it. So when do you paginate the response? The answer is pretty neat; you paginate whenever you want to process result in chunks. Some common scenarios are

- Batch processing
- Showing huge set of results on user interface

There are multiple approaches through which you can [paginate your result set in MongoDB](/blogs/fast-and-efficient-pagination-in-mongodb). This blog post is dedicated for results of benchmark of two approaches and its analysis, so here we go ...

Benchmark has been done over a non-indexed collection. Each document of the collection looks something like this
```js
    {
        "_id" : ObjectId("5936d17263623919cd5165bd"),
        "name" : "Lisa Rogers",
        "marks" : 34
    }
```

All records of a collection are fetched page-wise. Size of each page is fixed during fetch of the collection. Each page is fetched _3_ times and average of, time to fetch one “page”, 3 is recorded.

Following image shows the how two approach fares against each other.

![MongoDB Pagination Benchmark Results](https://user-images.githubusercontent.com/4745789/63220692-cb3ec380-c1aa-11e9-9882-27bf52cbaa84.png)

A key observation to note is that, till 500-600 count, both the approaches are comparable, but once it crosses that threshold, there is sudden rise in response time for `skip` and `limit` approach than other. The approach using `_id` and `limit` almost gives constant performance and is independent of size of the result set.

I tried running this test on different machines with different disks but results were similar. I think diving deep in MongoDB's database drivier will yield better information about this behavior. You could see some spikes in the response times, that are because of Disk Contention.

In short:
 - For huge result set, paginating using `_id` and `limit` is far better than using `skip` and `limit`.
 - For smaller result set, it does not matter, but prefer skip and limit.

An interesting thing I observed is that after page size crosses 100, the gap between the two approach reduces to some extent. I am yet to perform detailed benchmark on that as such use-case (where page-size is more than 100) is pretty rare in practical applications.

You can find the Python code used for this benchmark [here](https://github.com/arpitbbhayani/mongo-pagination-benchmark). If you have any suggestion or improvement, do let me know.
