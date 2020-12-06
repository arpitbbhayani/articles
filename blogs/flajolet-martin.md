Measuring the number of distinct elements from a stream of values is one of the most common utilities that finds its application in the field of Database Query Optimizations, Network Topology, Internet Routing, Big Data Analytics, and Data Mining.

A deterministic count-distinct algorithm either demands a large auxiliary space or takes some extra time for its computation. But what if, instead of finding the cardinality deterministically and accurately we just approximate, can we do better? This was addressed in one of the first algorithms in approximating count-distinct introduced in the seminal paper titled [Probabilistic Counting Algorithms for Data Base Applications](http://algo.inria.fr/flajolet/Publications/FlMa85.pdf) by Philippe Flajolet and G. Nigel Martin in 1984.

In this essay, we dive deep into this algorithm and find how wittily it approximates the count-distinct by making a single pass on the stream of elements and using a fraction of auxiliary space.

# Deterministic count-distinct

The problem statement of determining count-distinct is very simple -

*Given a stream of elements, output the total number of distinct elements as efficiently as possible.*

![https://user-images.githubusercontent.com/4745789/101273043-250c3800-37b8-11eb-9e0c-435e386f3529.png](https://user-images.githubusercontent.com/4745789/101273043-250c3800-37b8-11eb-9e0c-435e386f3529.png)

In the illustration above the stream has the following elements `4`, `1`, `7`, `4`, `2`, `7`, `6`, `5`, `3`, `2`, `4`, `7` and `1`. The stream has in all `7` unique elements and hence it is the count-distinct of this stream.

Deterministically computing count-distinct is an easy affair, we need a data structure to hold all the unique elements as we iterate the stream. Data structures like [Set](https://en.wikipedia.org/wiki/Set_(abstract_data_type)) and [Hash Table](https://en.wikipedia.org/wiki/Hash_table) suit this use-case particularly well. A simple pythonic implementation of this approach is as programmed below

```python
def cardinality(elements: int) -> int:
    return len(set(elements))
```

Above deterministic approach demands an auxiliary space of `O(n)` so as to accurately measure the cardinality. But when we are allowed to approximate the count we can do it with a fraction of auxiliary space using the Flajolet-Martin Algorithm.

# The Flajolet-Martin Algorithm

The Flajolet-Martin algorithm uses the position of the rightmost set and unset bit to approximate the count-distinct in a given stream. The two seemingly unrelated concepts are intertwined using probability. It uses extra storage of order `O(log m)` where `m` is the number of unique elements in the stream and provides a practical estimate of the cardinalities.

## The intuition

Given a good uniform distribution of numbers, the probability that the rightmost set bit is at position `0` is `1/2`, probability of rightmost set bit is at position `1` is `1/2 * 1/2 = 1/4`, at position `2` it is `1/8` and so on.

![https://user-images.githubusercontent.com/4745789/101275842-e635ac80-37ce-11eb-9e00-357b966cbac6.png](https://user-images.githubusercontent.com/4745789/101275842-e635ac80-37ce-11eb-9e00-357b966cbac6.png)

In general, we can say, the probability of the rightmost set bit, in binary presentation, to be at position `k` in a uniform distribution of numbers is

![https://user-images.githubusercontent.com/4745789/101275886-357bdd00-37cf-11eb-9bc6-346332031eb2.png](https://user-images.githubusercontent.com/4745789/101275886-357bdd00-37cf-11eb-9bc6-346332031eb2.png)

The probability of the rightmost set bit drops by a factor of `1/2` with every position from the Least Significant Bit to the Most Significant Bit.

![https://user-images.githubusercontent.com/4745789/101276356-1cc0f680-37d2-11eb-858d-3f40061988f0.png](https://user-images.githubusercontent.com/4745789/101276356-1cc0f680-37d2-11eb-858d-3f40061988f0.png)

So if we keep on recording the position of the rightmost set bit for every element in the stream (assuming uniform distribution) we should expect `ρ = 0` to be `0.5`, `ρ = 1` to be `0.25`, and so on. This probability should become `0` when bit position, `b` is `b > log n` while it should be non-zero when `b <= log n` where `n` is the number of distinct elements in the stream.

Hence, if we find the rightmost unset bit position `b` such that the probability is `0`, we can say that the number of unique elements will approximately be `2 ^ b`. This forms the core intuition behind the Flajolet Martin algorithm.

## Ensuring uniform distribution

The above intuition and approximation are based on the assumption that the distribution of the elements in the stream is uniform, which cannot always be true. The elements can be sparse and dense in patches. To ensure uniformity we hash the elements using a multiplicative hash function

![https://user-images.githubusercontent.com/4745789/98463097-f7df6080-21de-11eb-8b61-a84ff7ad85de.png](https://user-images.githubusercontent.com/4745789/98463097-f7df6080-21de-11eb-8b61-a84ff7ad85de.png)

where `a` and `b` are odd numbers and `c` is the capping limit of the hash range. This hash function hashes the elements uniformly into a hash range of size `c`.

## The procedure

The procedure of the Flajolet-Martin algorithm is as elegant as its intuition. We start with defining a closed hash range big enough to hold the maximum number of unique values possible - something as big as `2 ^ 64`. Every element of the stream is passed through a hash function that permutes the elements in a uniform distribution.

For this hash value, we find the position of the rightmost set bit and mark the corresponding position in the bit vector as `1`, suggesting that we have seen it. Once all the elements are processed, we find the position, say `b`, of the rightmost `0` in this bit vector.

This position `b` corresponds to the rightmost set bit that we have not yet seen, making its probability `0`; and hence we return the approximate cardinality as `2 ^ b`. Python-based code for this algorithm is as illustrated below

```python
# Size of the bit vector
L = 64

def hash_fn(x: int):
    return (3 * x + 5) % (2 ** L)

def cardinality_fm(stream) -> int:
    # we initialize the bit vector
    vector = 0

    # for every element in the stream
    for x in skream:
        
        # compute the hash value bounded by (2 ** L)
        # this hash value will ensure uniform distribution
        # of elements of the stream in range [0, 2 ** L)
        y = hash_fn(x)

        # find the rightmost set bit
        k = get_rightmost_set_bit(y)

        # set the corresponding bit in the bit vector
        vector = set_bit(vector, k)

    # find the rightmost unset bit in the bit vector that
    # suggests that the probability being 0
    b = rightmost_unset_bit(vector)

    # return the approximate cardinality
    return 2 ** b
```

The time complexity if O(n) while space complexity is O(log m)

Although the above algorithm does a decent job of approximating count-distinct it has a huge error margin, which can be fixed by averaging the approximations with multiple hash functions. The original Flajolet-Martin algorithm also suggests that the approximation needs a correction by diving the approximation by  `ϕ = 0.77351`.

The detailed source code of this algorithm can be found [here](https://github.com/arpitbbhayani/flajolet-martin/blob/master/flajolet-martin.ipynb). The algorithm was run on a stream size of `1048` with a varying number of distinct elements and we get the following plot.

![https://user-images.githubusercontent.com/4745789/101244923-58ef4b00-372f-11eb-9193-8e9d6dc6a227.png](https://user-images.githubusercontent.com/4745789/101244923-58ef4b00-372f-11eb-9193-8e9d6dc6a227.png)

From the illustration above we see that the approximated count-distinct using the Flajolet-Martin algorithm is very close to the actual deterministic value.

A great feature of this algorithm is that the result of this approximation algorithm will be the same whether the elements appear a million times or just a few times, as we just consider the rightmost set bit across all elements and do not even sample.

### Unique words in Thee Jungle Book

The above algorithm was run on the [The Jungle Book](https://en.wikipedia.org/wiki/The_Jungle_Book) by Rudyard Kipling and post tokenization it was found that the actual number of unique words in the corpus is `7150` while according to the Flajolet-Martin algorithm the approximated number of distinct words is `7606`, which is pretty close to the actual number.

# References

- [Probabilistic Counting Algorithms for Data Base Applications](http://algo.inria.fr/flajolet/Publications/FlMa85.pdf)
- [Flajolet-Martin algorithm by Ravi Bhide](http://ravi-bhide.blogspot.com/2011/04/flajolet-martin-algorithm.html)
- [The Jungle Book by Rudyard Kipling - Project Gutenberg](https://www.gutenberg.org/files/236/236-h/236-h.htm)