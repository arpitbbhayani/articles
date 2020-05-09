Binary Search is a search algorithm that finds the position of a target value in a sorted array. The algorithm exploits that fact that the array is sorted, and using this the algorithm does not even need to traverse all `n` elements of the array but it only needs to check `log(n)` elements to find the target value.

The binary search outputs the position of the target value, if present, otherwise it returns the position where the target value should be been present in the array. In other words we can say that the algorithm outputs the position where the target value should be inserted.

Here is the graph that shows how efficient is binary search. We plot the number of comparisons required to find the target value in a array of `n` elements. Even for a million values the binary search just need to look at 20 elements to deduce if the target value exists or not.

Fractional Cascading comes into the picture when we need to perform binary search on, not one but `k` such arrays. We take a look at several approaches to solve this problem and then we dive deep into the algorithm in spotlight - Fractional Cascading. Thus we define the problem statement as

> Given `k` lists of `n` integers and a target value `x`, find. Preprocessing is allowed.

# The naive approach - k binary searches
As the problem suggests, we need to find `x` in `k` arrays. we do `k` binary searches.
TODO: Image

## Complexity

Complexity: `k.log(n)`

# Merge all lists in one

We can merge all the `k` lists in one and do binary search just once instead of `k`.

## Preprocess

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

## Preprocess

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
