Binary Search is a search algorithm that finds the position of a target value in a sorted array. The algorithm exploits that fact that the array is sorted, and is devised such that is need not even look at all `n` elements to decide if the target value is present or not. IN worst case the algorithm checks for `log(n)` elements of the array to make the decision.

Having to check only `log(n)` elements from the array of size `n` is super eficient - this means in an array of size of a million `1000000` the number of elemnts to be looked at to make the call is just `20`. need to look at 20 elements to deduce if the target value exists or not. Binary search could be tewaked to output the position of the target value, if present, or otherwise returns the position of smallest number greater than the target value i.e. position where the target value should have been present in the array.

Things become slightly moer interesting when instead of searching for the target value in one array, we need to do it in `k` arrays. Problem statement could be defined as

> Given `k` lists of `n` integers each and a target value `x` return the position of the smallest value greater than or equal to `x` in each of the `k` lists. We are allowed to preprocess the lists.

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
