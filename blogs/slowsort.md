Slowsort is a sorting algorithm that is designed to be deterministically sub-optimal. The algorithm was published in 1986 by Andrei Broder and Jorge Stolfi in their paper [Pessimal Algorithms and Simplexity Analysis](https://www.researchgate.net/publication/2805500_Pessimal_Algorithms_and_Simplexity_Analysis) where they expressed a bunch of very in-efficient algorithms. These techniques and algorithms are special because they never make a wrong move while solving a problem, instead, they find ways to delay the success. In this essay, we put our focus on the Slowsort algorithm based on the *Multiply and Surrender* paradigm.

# Multiply and Surrender

The *Multiply and Surrender (MnS)* paradigm, is a humorous take on the popular *Divide and Conquer (DnC)* technique. MnS splits the problem into subproblems, slightly simpler than the original, and continues doing so recursively for as long as possible. The subproblems are multiplied and the evaluation is delayed till the state that the solving could not be further postponed and then it surrenders.

MnS paradigm is very similar to DnC; but where the DnC actually splits the problems into subproblems to reach the solution quicker, MnS does it to procrastinate, making the entire process very inefficient but yet convergent.

Although Slowsort is a classic example, recursive Fibonacci with no memoization also fares under the MnS paradigm. The recursive code to find `n`th Fibonacci number is as illustrated below

```python
def fib(n):
    """the function returns the `n`th fibonacci number
    """

    # the subproblem could not be postponed anymore
    # hence we surrender and return the answer
    if n < 2:
        return 1

    # we split the problem into subproblems and invoke
    # the function recursively
    return fib(n - 1) + fib(n - 2)
```

While computing the Fibonacci numbers, we split the problem into subproblems and do this recursively till we are left with elemental states i.e. `0` or `1` and which is when we return the initial values which are `1` and `1`. This approach is not DnC because we are not splitting the problem into subproblems to achieve optimality, instead are doing a lot of repetitive work and taking a non-polynomial time to generate the Fibonacci numbers.

# Slowsort Algorithm

Slowsort algorithm draws a lot of similarities to the very popular Mergesort, but while Mergesort operates in `O(n . log(n))` the complexity of Slowsort is non-polynomial `O(n ^ log(n))` and its best case performs worse than the worst case of bubble sort.

Slowsort algorithm recursively breaks the array sorting problem into two subarray sorting problems and a few extra processing steps. Once the two subarrays are sorted, the algorithm swaps the rightmost elements such that the greatest among the two becomes the rightmost element of the array i.e. the greatest among the two is placed at the correct position relative to each other, and then it invokes the sorting for all elements except this fixed maximum.

The algorithm could this be expressed as following broad steps

- sort the first half recursively
- sort the second half recursively
- find the maximum of the whole array by comparing the last elements of both the sorted halves and place it at the end of the array
- recursively sort the entire array except for the maximum one

The in-place implementation of the Slowsort algorithm is as illustrated below

```python
def _slowsort(a, i, j):
    """in-place sorts the integers in the array
    spanning indexes [i, j].
    """
    # base condition; then no need of sorting if
    #  - there is one element to sort
    #  - when start and end of the array flipped positions
    if i >= j:
        return

    # find the mid index of the array so that the
    # problem could be divided intto sub-problems of
    # smaller spans
    m = (i + j) // 2

    # invoke the slowsort on both the subarrays
    _slowsort(a, i, m)
    _slowsort(a, m + 1, j)
  
    # once both the subproblems are solved, check if
    # last elements of both subarrays and move the
    # higher among the both to end of the right subarray
    # ensuring that the highest element is placed at the
    # correct relative position
    if a[m] > a[j]:
        a[m], a[j] = a[j], a[m]
  
    # now that the rightmost element of the array is at
    # the relatively correct position, we invoke Slowsort on all
    # the elements except the last one.
    _slowsort(a, i, j - 1)


def slowsort(a):
    """in-place sorts the array `a` using Slowsort.
    """
    _slowsort(a, 0, len(a) - 1)
```

The Slowsort algorithm typically replaces the `merge` function of the Mergesort with a simple swap that correctly places the largest element (local maxima) and then invokes the sort function on all but this element. So on every invocation, we keep correctly placing the largest element but in a recursive manner.

*A visualization of this algorithm could be found in this [youtube video](https://www.youtube.com/watch?v=QbRoyhGdjnA).*

# Asymptotic Analysis

The runtime of Slowsort could be computed by the following recurrence relation

![slowsort recurrence relation](https://user-images.githubusercontent.com/4745789/88473102-cb594e80-cf37-11ea-9015-217c3eda50d6.png)

When the above recurrence relation is solved and we find that the asymptotic lower bound for `T(n)` is given by

![lower bound of slowsort](https://user-images.githubusercontent.com/4745789/88473128-14a99e00-cf38-11ea-905b-f3f473a0d74c.png)

The above expression suggests that lower bound of Slowsort is non-polynomial in nature and for a sufficiently large `n` this would be more than `n ^ 2` implying that even the best case of Slowsort is worse than the worst case of Bubble sort. The illustration below compares the time taken by Slowsort and the recursive implementation of Bubblesort.

![slowsort vs recursive bubblesort](https://user-images.githubusercontent.com/4745789/88475549-8e4c8680-cf4e-11ea-8ee4-9f7ed345ff5d.png)

> The iterative implementation of Bubblesort stood no chance in terms of time taken for smaller sets of integers, hence the chart was plotted against the recursive implementation of it. The iterative bubble sort for smaller arrays is nearly flat.

# Slowsort vs Bogosort

[Bogosort](https://en.wikipedia.org/wiki/Bogosort) is a sorting algorithm that has an average case time complexity of `O(n!)` and an unbounded time in the worst case. The algorithm keeps on permuting (shuffling) the array till it is sorted which introduces an unboundedness in its implementation and hence the algorithm is considered to be the worst sorting algorithm ever.

```python
import random

def is_sorted(a):
    return all(a[i] <= a[i + 1] for i in range(len(a) - 1))

def bogosort(a):
    while not is_sorted(a):
        random.shuffle(a)
```

The reason that we should rate Slowsort highly is the fact the Bogosort could sort the list in its first shuffle while Slowsort is deterministic and will take `O(n ^ log(n))` time in best case scenario.

A rule that every algorithm follows is that every step that it takes actually makes some progress towards the final goal. Bogosort does not guarantee progress, and since it randomly shuffles the array, at one iteration we could end up at a nearly sorted array while the next shuffle takes us afar.

Slowsort is deterministic and convergent. The number of swaps made (inversions) during the execution is non-increasing which means once two items are swapped they are in the correct order relative to each other. In other words, we say that Slowsort never makes a wrong move.

# References

- [Slowsort](https://wiki.c2.com/?SlowSort)
- [Slowsort - Wikipedia](https://en.wikipedia.org/wiki/Slowsort)
- [Multiply and Surrender](https://wiki.c2.com/?MultiplyAndSurrender)
- [Pessimal Algorithms and Simplexity Analysis](https://www.researchgate.net/publication/2805500_Pessimal_Algorithms_and_Simplexity_Analysis)
