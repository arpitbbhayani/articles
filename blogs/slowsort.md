Slowsort is a sorting algorithm that is designed to be deterministically sub-optimal. The algorithm was published in 1986 by Andrei Broder and Jorge Stolfi in their paper [Pessimal Algorithms and Simplexity Analysis](https://www.researchgate.net/publication/2805500_Pessimal_Algorithms_and_Simplexity_Analysis) where they expressed a bunch of very in-efficient algorithms. These techniques and algorithms are special because they never make a wrong move while solving a problem, instead they find ways to delay the success. In this essay we put our focus on Slowsort algorithm based on *Multiply and Surrender* paradigm.

# Multiply and Surrender

The *Multiply and Surrender (MnS)* paradigm, is a humorous take on the popular *Divide and Conquer (DnC)* technique. MnS splits the problem into subproblems, slightly simpler than the original, and continues doing so recursively for as long as possible. The subproblems are multiplied and the solution computation is delayed till the state that the solving could not be further postponed and then it surrenders.

MnS paradigm is very similar to DnC; but where the DnC actually splits the problems into subproblems to reach to the solution quicker, MnS does it to procrastinate making the entire process very inefficient yet convergent.

Although Slowsort is a classic example, recursive Fibonacci with no memoization also fares under MnS paradigm. The recursive code to find `n`th fibonacci number is as illustrated below

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

While computing the Fibonacci numbers, we split the problem into subproblems and do this recursively till we are left with elemental states i.e. `0` or `1` and which is when we return the initial values which are `1` and `1`. This approach is not divide and conquer because we are not splitting the problem into subproblems to achieve optimality, instead are doing a lot of repetitive work while taking a non-polynomial time to generate the Fibonacci numbers.

# Slowsort Algorithm

Slowsort algorithm draws a lot of similarities to the very popular Mergesort; but while Mergesort operates in `O(nlogn)` the complexity of Slowsort is non-polynomial and its best-case performs worse than the worst-case of bubble sort.

Slowsort algorithms recursively breaks the array sorting problem into two subarray sorting problems. Once the two subarrays are sorted, the algorithm swaps the rightmost elements of the two sorted subarrays such that the greatest among the two becomes the rightmost element of the array i.e. the greatest among the two is placed at the correct position; and then it invokes the sorting for all elements except the fixed maximum.

The algorithm could be stated as follows

- sort the first half recursively
- sort the second half recursively
- find the maximum of the whole array by comparing the last elements of both the sorted halves and place it at the end of the array
- recursively sort the entire list except the maximum one

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
    # correct position
    if a[m] > a[j]:
        a[m], a[j] = a[j], a[m]
  
    # now that the rightmost element of the array is at
    # the correct position, we invoke slowsort on all the elemnts
    # except the last one.
    _slowsort(a, i, j - 1)

def slowsort(a):
    """in-place sorts the array `a` using Slowsort.
    """
    _slowsort(a, 0, len(a) - 1)
```

The Slowsort algorithm typically replaces the `merge` function of the Mergesort with a simple swap that correctly places the largest element and then invokes the sort function on all but this elements. So on every invocation we keep correctly placing the largest element but in a recursive manner.

*A visualization of this algorithm could be found in this [youtube video](https://www.youtube.com/watch?v=QbRoyhGdjnA).*

# Asymptotic Analysis

The runtime of Slowsort could be computed by the following recurrence relation

![https://user-images.githubusercontent.com/4745789/88473102-cb594e80-cf37-11ea-9015-217c3eda50d6.png](https://user-images.githubusercontent.com/4745789/88473102-cb594e80-cf37-11ea-9015-217c3eda50d6.png)

When the above recurrence relation is solved and we compute the asymptotic lower bound for `T(n)`, we find that is given by

![https://user-images.githubusercontent.com/4745789/88473128-14a99e00-cf38-11ea-905b-f3f473a0d74c.png](https://user-images.githubusercontent.com/4745789/88473128-14a99e00-cf38-11ea-905b-f3f473a0d74c.png)

The above expression suggests that lower bound of Slowsort is non-polynomial in nature and for a sufficiently large `n` this would be more than `n^2` implying that even the best case of Slowsort is worse than worst case of Bubble sort. The illustration below compares the time taken by Slowsort and recursive implementation of Bubblesort.

![https://user-images.githubusercontent.com/4745789/88473298-afef4300-cf39-11ea-9c14-638e03791199.png](https://user-images.githubusercontent.com/4745789/88473298-afef4300-cf39-11ea-9c14-638e03791199.png)

> The iterative implementation of Bubblesort stood no chance in terms of time taken for smaller sets of integers, hence the chart was plotted against recursive implementation of it.

# Slowsort vs Bogosort

Bogosort is a sorting algorithm that has a time complexity of `O(n!)` in average case and an unbounded time in the worst case. The algorithm keeps on permuting (shuffling) the array till it is sorted and because of this unboundedness is considered to be the worst sorting algorithm ever.

```python
import random

def is_sorted(a):
    return all(a[i] <= a[i + 1] for i in range(len(a) - 1))

def bogosort(a):
    while not is_sorted(a):
        random.shuffle(a)
```

The reason that we should rate Slowsort heavy is the fact the the Bogosort could sort the list in its first shuffle while Slowsort is deterministic and will take `O(n ^ log(n))` time in best-case.

A rule that every algorithm follows is that every step that it takes, actually makes some progress towards the goal. Bogosort does not guarantee progress, as it randomly shuffles, one iteration could transform array to its sorted form while the next one takes it a far.

But Slowsort is deterministic and convergent. The number of swaps made (inversions) during ithe execution are non-increasing which means once two items are swapped they are in correct order relative to each other. In other words we say that Slowsort never makes a wrong move.

# References

- [Slowsort](https://wiki.c2.com/?SlowSort)
- [Slowsort - Wikipedia](https://en.wikipedia.org/wiki/Slowsort)
- [Multiply and Surrender](https://wiki.c2.com/?MultiplyAndSurrender)
- [Pessimal Algorithms and Simplexity Analysis](https://www.researchgate.net/publication/2805500_Pessimal_Algorithms_and_Simplexity_Analysis)

---

# Other articles that you might like

- [Python Caches Integers](https://arpitbhayani.me/blogs/python-caches-integers)
- [Fractional Cascading - Speeding up Binary Searches](https://arpitbhayani.me/blogs/fractional-cascading)
- [Copy-on-Write Semantics](https://arpitbhayani.me/blogs/copy-on-write)
- [What makes MySQL LRU cache scan resistant](https://arpitbhayani.me/blogs/mysql-cache)

---

If you liked what you read, consider subscribing to my weekly newsletter at [arpitbhayani.me/newsletter](https://arpitbhayani.me/newsletter) where, once a week, I write an essay about programming languages internals, or a deep dive on some super-clever algorithm, or just a few tips on building highly scalable distributed systems.

You can always find me browsing through twitter [@arpit_bhayani](https://twitter.com/arpit_bhayani).