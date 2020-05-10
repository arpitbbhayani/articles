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
This approach uses extra space to reduce the search time. It processess, precomputes and stores the position of each element in all the lists and serves the result by performing binary search just once. Thus each element is now associated with a tuple with `k` items where every `i`th each item represents its position in `i`it list.

## Preprocess

The preprocessing is done in two folds; in the first phase we compute position tuple for each element while in second we create an auxiliary list containing all the elements of all the lists.

### Create position tuple for each element
The position tuple is a `k` item tuple where every `i`th item denotes the position of the associated element in `i`th list. Thus the tuple for an element is computed by performing binary search on all `k` lists by treating the element as the target value.

Python code to compute position tuple for all elements in 2 dimensional array `arr` is as shown below

```py
for i, l in enumerate(arr):
    for j, e in enumerate(l):
        for k, m in enumerate(arr):
            positions[i][j][k] = int(bisect.bisect_left(m, e))
```

In above example, the position tuple of 4th element in 4th list i.e `79` is `[3, 5, 4, 3]`.

### Creating a huge list
Once we have position tuple associated with each element, we create an auxiliary list containing all the elements (with its position tuple associations) of all the `k` lists. Thus we create a huge list of in all `kn` number of elments and arrange them in sorted order.

![unified binary search](https://user-images.githubusercontent.com/4745789/81492609-ca107200-92b6-11ea-8fdf-999852f4d9b1.png)

## Working
Given a target value, we perform binary search in the above auxiliary list created and get the smallest element greater than  or equal to this target value. Once we get the element, we now get the associated position tuple. This position tuple is precisely the positions of the target element in all the `k` lists. Thus by performing one binary search in this huge list we are able to get the required positions.

## Complexity
We are performing binary search just once on the list of size `kn` hence, the time complexity of this approach is `O(log(kn))` which is a huge improvement over the k-binary search approach where it was `O(klog(n))`.

This approach, unlike k-binary searches, requires a huge additional space of `O(kn)`.

Fractional cascading is something that gives us the best of both words by creating bridges. Let's find out how.

# Fractional Cascading
Fractional cascading is a technique through which we speed up the iterative binary searches by creating bridges between lists. The main idea behind this approach is to dampen, rather avoid, the need to perform binary searches in `n - 1` lists.

In the first approach we saw how a naive way to solve this problem is to perform `k` binary searches for `k` lists; but by closely observing we find that a lot of binary search iterations on 2nd and onwards list could be avoided by just reducing the scope. The idea here is to preprocess the lists such that we create pointers from one list to another that defines a super-narrow scope for binary search. so that instead of doing binary search across the entire list, we look for the number only in that narrowed scope.

![Fractional Cascading the Idea](https://user-images.githubusercontent.com/4745789/81495324-241c3200-92cd-11ea-9d7d-9c9b0911071b.png)

Fractional cascading is just an idea through which we could speed up binary searches, implementations vary with respect to underlying data. The cascading could be implemnted using pointers, graphs or array indexes and in this example we keep things simple and implement everything using indexes.

## Preprocess
Preprocessing is a super-critical step in fractional cascading becuase this is something that is respondible of speeding up the binary searches. Preprocesing actually sets up all the bridges we need to traverse through the k lists.

### Create Auxiliary Lists
The first step in pre-processing is to create `k` auxiliary lists from `k` original lists. These lists are created bottom up such that auxiliary list `Mi` is created as a sorted list of elements of `Li` and half of the elements of `Mi+1`. The half elements are picked by picing every other element.

THis is necessary to fill the gaps, if any, in the original list and create a uniform spread of values.

![Create Auxiliary Lists](https://user-images.githubusercontent.com/4745789/81494077-8112ea80-92c3-11ea-9416-bb2422334744.png)


### Create position pointers

![Create position pointerss](https://user-images.githubusercontent.com/4745789/81494709-92122a80-92c8-11ea-89c0-e180a735eb2d.png)

Each number is represented by [a, b]

## Working

## Code

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
