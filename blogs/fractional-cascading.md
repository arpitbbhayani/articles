Binary Search is an algorithm that finds the position of a target value in a sorted list. The algorithm exploits the fact that the list is sorted, and is devised such that is does not have to even look at all the `n` elements, to decide if a value is present or not. In the worst case, the algorithm checks the `log(n)` number of elements to make the decision.

Binary Search could be tweaked to output the position of the target value, or return the position of the smallest number greater than the target value i.e. position where the target value should have been present in the list.

Things become more interesting when we have to perform an iterative binary search on `k` lists in which we find the target value in each of the `k` lists independently. The problem statement could be formally defined as

> Given `k` lists of `n` sorted integers each, and a target value `x`, return the position of the smallest value greater than or equal to `x` in each of the `k` lists. Preprocessing of the list is allowed before answering the queries.

# The naive approach - k binary searches
The expected output of this iterative search is the position of smallest value greater than or equal to `x` in each of the `k` lists. This is a classical Binary Search problem and hence in this, the naive approach we could fire `k` binary searches on `k` lists for the target value `x` and collect the positions. A simple enough solution that works just fine.

![k-binary searches](https://user-images.githubusercontent.com/4745789/81492614-dbf21500-92b6-11ea-9f75-29eb3522186f.png)

Python has an in-built module called `bisect` which has the function `bisect_left` which outputs the smallest value greater than or equal to `x` in a list `l`; which is exactly what we need to output and hence python-based solution using this k-binary searches approach could be 

```py
import bisect

arr = [
    [21, 54, 64, 79, 93],
    [27, 35, 46, 47, 72],
    [11, 44, 62, 66, 94],
    [10, 35, 46, 79, 83],
]

def get_positions_k_bin_search(x): 
    return [bisect.bisect_left(l, x) for l in arr]

>>> get_positions_k_bin_search(60)
[2, 4, 2, 3]
```

## Time and Space Complexity
Each of the `k` lists has size `n` and we know the time complexity of performing a binary search in one list of `n` elements is `O(log(n))`. Hence we deduce that the time complexity of this k-binary searches approach is `O(klog(n))`. 

This approach does not really require any additional space and hence the space complexity is `O(1)`.

The k-binary searchs approach is thus super-efficient on space but not so much on time. Hence by trading some space, we could get some benefits on time complexity and on this principle, the unified binary search approach is based.

# Unified binary search
This approach uses extra space to reduce search time. It processes, precomputes, and stores the position of each element in all the lists and serves the result by performing a binary search just once. Thus each element is now associated with a tuple with `k` items where every `i`th each item represents its position in `i`it list.

## Preprocess

The preprocessing is done in two folds; in the first phase, we compute position tuple for each element while in the second we create an auxiliary list containing all the elements of all the lists.

### Create position tuple for each element
The position tuple is a `k` item tuple where every `i`th item denotes the position of the associated element in `i`th list. Thus the tuple for an element is computed by performing binary search on all `k` lists by treating the element as the target value.

Python code to compute position tuple for all elements in 2-dimensional array `arr` is as shown below

```py
for i, l in enumerate(arr):
    for j, e in enumerate(l):
        for k, m in enumerate(arr):
            positions[i][j][k] = int(bisect.bisect_left(m, e))
```

In the above example, the position tuple of 4th element in 4th list i.e `79` is `[3, 5, 4, 3]`.

### Creating a huge list
Once we have position tuple associated with each element, we create an auxiliary list containing all the elements (with its position tuple associations) of all the `k` lists. Thus we create a huge list of in all `kn` number of elements and arrange them in sorted order.

![unified binary search](https://user-images.githubusercontent.com/4745789/81492609-ca107200-92b6-11ea-8fdf-999852f4d9b1.png)

## Working
Given a target value, we perform a binary search in the above auxiliary list created and get the smallest element greater than or equal to this target value. Once we get the element, we now get the associated position tuple. This position tuple is precisely the position of the target element in all the `k` lists. Thus by performing one binary search in this huge list, we are able to get the required positions.

## Complexity
We are performing binary search just once on the list of size `kn` hence, the time complexity of this approach is `O(log(kn))` which is a huge improvement over the k-binary searches approach where it was `O(klog(n))`.

This approach, unlike k-binary searches, requires a huge additional space of `O(kn)`.

Fractional cascading is something that gives us the best of both words by creating bridges. Let's find out how.
