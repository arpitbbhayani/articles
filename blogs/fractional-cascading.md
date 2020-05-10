Binary Search is an algorithm that finds the position of a target value in a sorted list. The algorithm exploits that fact that the list is sorted, and is devised such that is does not even look at all `n` elements to decide if the target value is present or not. In worst case the algorithm checks `log(n)` number of elements to make the decision.

Binary search could be tweaked to output the position of the target value, if present, or otherwise returns the position of smallest number greater than the target value i.e. position where the target value should have been present in the list.

Things become more interesting when we have to perform iterative search on `k` lists i.e. finding the target values in each of the `k` list independently. The formal problem statement could be defined as

> Given `k` lists of `n` sorted integers each and a target value `x` return the position of the smallest value greater than or equal to `x` in each of the `k` lists. Preprocessing of the list is allowed before answering queries.

# The naive approach - k binary searches
The expected output of this iterative search is the position of smallest value greater than or equal to `x` in each of the `k` lists. This is a classical Binary search problem that could be applied on each of the `k` lists.

![k-binary searches](https://user-images.githubusercontent.com/4745789/81492614-dbf21500-92b6-11ea-9f75-29eb3522186f.png)

A python based solution to this problem is pretty simple. We use in-built module `bisect` and `bisect_left` function returns the exact thing we are looking for

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
Each of the `k` list has size `n` and we know the time complexity of performing a binary search in one list of `n` elements is `O(log(n))`, we deduce that time complexity of this approach of k-binary searches is `O(k.log(n))`. 

The k-binary searches approach does not reqlly require any additional space and hence the space complexity is `O(1)`.

# Unified binary search
This approach combines all the elements of all the `k` lists and creates an auxiliary list of size `kn` and performs binary search on this. While creating this this, it also creates a vector for each element that represents `k`-tuple containing position of that elment in each of the `k` list. Hence this approach is split into two phases

## Preprocess

### Create position vector for each element
For every element in all the `k` lists we create a `k` sizes tuple for each. This tuple will hold position of the element in each of the `k` lists. The first position in the tuple is the position of the element in the 1st list, second position in the tuple is the position of the element in the 2nd list, and so on.

`[2, 3, 3, 4]`

This way we have precomputed all the position of every single element in all the `k` lists.

### Creating a huge list
The step one of this approach is to create an auxiliary list of all the elements of `k` lists and put them in sorted order in another list.

## Working

When when a target value is to be searched, we search it in this huge list `M`, get the position by regular binary search. and return the position tuple associated with it.

![unified binary search](https://user-images.githubusercontent.com/4745789/81492609-ca107200-92b6-11ea-8fdf-999852f4d9b1.png)

## Complexity

This approach uses `O(kn)` extra space but does it on `O(log(kn))` time


Time Complexity: `k + log(n)`
Space Complexity: `O(kn)`

Can we have best of both worlds? Fractional cascading is how you can acive time complexity of approach 2 and space of approach 1.

# Fractional Cascading

Speeds up binary search.
Creates bridges and fences.

Concept

![Fractional Cascading the Idea](https://user-images.githubusercontent.com/4745789/81495324-241c3200-92cd-11ea-9d7d-9c9b0911071b.png)

## Preprocess

### Create Auxiliary Lists

![Create Auxiliary Lists](https://user-images.githubusercontent.com/4745789/81494077-8112ea80-92c3-11ea-9416-bb2422334744.png)


### Create position pointers

![Create position pointerss](https://user-images.githubusercontent.com/4745789/81494709-92122a80-92c8-11ea-89c0-e180a735eb2d.png)

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
