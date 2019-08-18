MongoDB’s cursor object has a method called `skip`, which as per [documentation and definition](https://docs.mongodb.com/manual/reference/method/cursor.skip/#definition), controls where MongoDB begins returning results. Thus in combination with function [limit](https://docs.mongodb.com/manual/reference/method/cursor.limit/), one can easily have paginated results.

I have written a blog post on [how you can have Fast and Efficient Pagination in MongoDB](/blogs/fast-and-efficient-pagination-in-mongodb).

But while going through the documentation of skip, there is something interesting to notice. There is a small warning in [MongoDB documentation](https://docs.mongodb.com/manual/reference/method/cursor.skip/#behavior), that states

  > The `cursor.skip()` method is often expensive because it requires the server to walk from the beginning of the collection or index to get the offset or skip position before beginning to return results. As the offset (e.g. `pageNumber` above) increases, `cursor.skip()` will become slower and more CPU intensive. With larger collections, `cursor.skip()` may become IO bound.

In short, MongoDB has to iterate over documents to skip them. Thus when collection or result set is huge and you need to skip documents for pagination, the call to `cursor.skip` will be expensive. While going through the source code of `skip` I found out that it does not use any index and hence gets slower when result set increases in size.

This also implies that if you use `skip`  then the “skipping speed” will not improve even if you index the field.

But what if the size of result set is small? is calling `skip` still a terrible idea?
If skip was so terrible, then MongoDB team and community must had taken that decision long back. But they haven’t … why?

Because it is very efficient and fast for smaller result set. I have taken this opportunity to [benchmark and compare](/blogs/benchmark-and-compare-pagination-approach-in-mongodb) the [two approach for pagination](/blogs/fast-and-efficient-pagination-in-mongodb) and there I found out skip and limit based pagination works well for smaller result sets.

In conclusion, skip is not as bad one might think. But you must understand your use case well so as to make an informed decision.
