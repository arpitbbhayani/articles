Binary Search is a search algorithm that finds the position of a target value in a sorted array. If the target value is present in the array, the algoritm returns the position. If it does not exist then the algorithm returns the posiiton where it should be inserted. The search happens in `O(log(n))`.

```py
import bisect

def binary_search(arr, q):
    return bisect.bisect_left(arr, q)
```

Fractional Cascading is a technique that speeds up binary searches for the same value in a sequence of 


# The two extremes

## k - binary searches

## Merge all in one

# Fractional Cascading

## Preprocessinf

## Working

## Code

## Time and space complexity

## The more interesting part

### Why does we need to only check for the element and one before?

### Instead of doing it for alternate and not all?

### What if we do one in three

# References
