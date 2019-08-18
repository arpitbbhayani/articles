[MongoDB](https://www.mongodb.com/) is a document based data store and hence pagination is one of the most common use case of it. So when do you paginate the response? The answer is pretty neat; you paginate whenever you want to process result in chunks. Some common scenarios are

- Batch processing
- Showing huge set of results on user interface

Paginating on client and server side are both really very expensive and should not be considered. Hence pagination is generally handled at database level and databases are optimized for such needs too.

Below I shall explain you the 2 approaches through which you can easily paginate your MongoDB responses.
Sample Document

```json
    {
        "_id" : ObjectId("5936d17263623919cd5165bd"),
        "name" : "Lisa Rogers",
        "marks" : 34
    }
```

## Approach 1: Using `cursor.skip` and `cursor.limit`

MongoDB cursor has two methods that makes paging easy; they are

- `cursor.skip()`
- `cursor.limit()`

`skip(n)` will skip `n` documents from the cursor while `limit(n)` will cap the number of documents to be returned from the cursor. Thus combination of two naturally paginates the response.

In Mongo Shell your pagination code looks something like this

```js
    // Page 1
    db.students.find().limit(5)

    // Page 2
    db.students.find().skip(5).limit(5)

    // Page 3
    db.students.find().skip(5).limit(5)
```

`.find()` will return a cursor pointing to all documents of the collection and then for each page we skip some and consume some. Through continuous skip and limit we get pagination in MongoDB.

I am fond of Python and hence here is a small trivial function to implement pagination:

```python
    def skiplimit(page_size, page_num):
        """returns a set of documents belonging to page number `page_num`
        where size of each page is `page_size`.
        """
        # Calculate number of documents to skip
        skips = page_size * (page_num - 1)

        # Skip and limit
        cursor = db['students'].find().skip(skips).limit(page_size)

        # Return documents
        return [x for x in cursor]
```

## Approach 2: Using `_id` and `limit`

This approach will make effective use of default index on `_id` and nature of `ObjectId`.
I bet you didn’t know that a [Mongodb ObjectId](https://docs.mongodb.com/manual/reference/bson-types/#objectid) is a 12 byte structure containing

- a 4-byte value representing the seconds since the Unix epoch,
- a 3-byte machine identifier,
- a 2-byte process id, and
- a 3-byte counter, starting with a random value.

Even I didn’t until I read the [documentation](https://docs.mongodb.com/manual/reference/bson-types/#objectid). Apart from its structure there is one very interesting property of ObjectId; which is - *ObjectId has natural ordering*

What does it mean? It simplifies that we can apply all the *less-than-s* and all the *greater-than-s you* want to it. If you don’t believe me, open Mongo shell and execute following set of commands

```javascript
    > ObjectId("5936d49863623919cd56f52d") > ObjectId("5936d49863623919cd56f52e")
    false
    > ObjectId("5936d49863623919cd56f52d") > ObjectId("5936d49863623919cd56f52a")
    true
```

Using this property of ObjectId and also taking into consideration the fact that `_id` is always indexed, we can devise following approach for pagination:

1. Fetch a page of documents from database
2. Get the document id of the last document of the page
3. Retrieve documents greater than that id

In Mongo Shell your pagination code looks something like this

```javascript
    // Page 1
    db.students.find().limit(10)

    // Page 2
    last_id = ...  # logic to get last_id
    db.students.find({'_id': {'$gt': last_id}}).limit(10)

    // Page 3
    last_id = ... # logic to get last_id
    db.students.find({'_id': {'$gt': last_id}}).limit(10)
```

Again, I am fond of Python and here is the Python implementation of this approach.

```python
    def idlimit(page_size, last_id=None):
        """Function returns `page_size` number of documents after last_id
        and the new last_id.
        """
        if last_id is None:
            # When it is first page
            cursor = db['students'].find().limit(page_size)
        else:
            cursor = db['students'].find({'_id': {'$gt': last_id}}).limit(page_size)

        # Get the data
        data = [x for x in cursor]

        if not data:
            # No documents left
            return None, None

        # Since documents are naturally ordered with _id, last document will
        # have max id.
        last_id = data[-1]['_id']

        # Return data and last_id
        return data, last_id
```

> If you are using a field other than `_id` for offset, make sure the field is indexed and properly ordered else the performance will suffer.

## Closing Remarks

Both of the above approaches are valid and correct. But as we know, in field of Computer Science, whenever there are multiple options to achieve something, one always outperforms the other. Same is the situation here as well.

Turns out, there is a severe problem with skip function. I have tried to jot it down in [this blog post](/blogs/mongodb-cursor-skip-is-slow). Because of which second approach has advantage over first. But that is not it; I wrote a simple [python code](https://github.com/arpitbbhayani/mongo-pagination-benchmark) to benchmark the two approaches for various combinations and it turns out `skip` performs better in some case. The results are compiled into [this blog post](/blogs/benchmark-and-compare-pagination-approach-in-mongodb).
