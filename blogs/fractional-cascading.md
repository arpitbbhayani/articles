Binary Search is a search algorithm that finds the position of a target value in a sorted array. If the target value is present in the array, the algoritm returns the position. If it does not exist then the algorithm returns the posiiton where it should be inserted. The search happens in `O(log(n))`.

Which means it does not even need to take a look at all the elements to find the target value. The approach seems super efficient and it actually is. As the number of items increases the lookup time increases marginally. Here is the graph representing that.

TODO: Graph

Taking this use case a notch higher. Say we need to find the target value, not in one, but `k` lists independently which means. For each list we need to find the position of the target value. Preprocessing is allowed.

# The naive approach - k binary searches

As the problem suggests, we need to find `x` in `k` arrays. we do `k` binary searches.
TODO: Image

## Complexity

Complexity: `k.log(n)`

# Merge all lists in one

We can merge all the `k` lists in one and do binary search just once instead of `k`.
Before before doing that we can just apply binary search for each term in each list and say we store
all the locations for each number in search list.

TODO: Image

Here [a,b,c,d] represents location of a number in each of the four lists.

## Complexity

Time Complexity: `k + log(n)`
Space Complexity: `O(kn)`

Can we have best of both worlds? Fractional cascading is how you can acive time complexity of approach 2 and space of approach 1.

# Fractional Cascading

Speeds up binary search.
Creates bridges and fences.

## Preprocessing

Each number is represented by [a, b]

## Working

## Code

```py
import bisect

def binary_search(arr, q):
    return bisect.bisect_left(arr, q)
```

The entire working code could be found here [github.com/arpitbbhayani/fractional-cascading](https://github.com/arpitbbhayani/fractional-cascading/blob/master/fractional-cascading.ipynb)

## Time and space complexity

## The more interesting part

### Why does we need to only check for the element and one before?
Since we take every other number from the list. This means the number was either 1st or second.

### Instead of doing it for alternate and not all?
If we do it for all, it becomes the nurmal search. Hence the name "Fractional" cascading.

### What if we do one in three
We can limit the number fo elements promoted to higher level. But in that that we need to compare with last `r` numbers prior to the matched value.

# References
