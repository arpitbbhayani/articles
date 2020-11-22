A queue is a data structure that holds up elements for a brief period of time until a peripheral processing system is ready to process them. The most common implementation of a queue is a FIFO queue - First In First Out - that evicts the element that was inserted the first i.e. it evicts the one that has spent the most time in the queue. There are other variations of Queues one of which is called Priority Queue.

In Priority Queue, every element is associated with a priority, usually provided by the user during enqueueing; This associated priority is used during eviction where the element with the highest priority is evicted first during dequeuing.

In this essay, we take a detailed look into a variation of Priority Queue, fondly called Israeli Queues, where the priority of the element is defined by the affinity of it with one of its "friends" in the queue. Israeli Queues were first introduced in the paper [Polling with batch service](https://pure.tue.nl/ws/files/2152975/632939.pdf) by Boxma, O. J., Wal, van der, J., & Yechiali, U in the year 2007.

# Israeli Queues

Queues in Israel are usually unorganized, due to which people tend to find their friends, who are already waiting, and instead of adhering to the usual protocol of joining at the back end, they cut through and directly join their friends. Israeli Queues mimic this behavior and hence get this [punny name](https://www.tandfonline.com/doi/abs/10.1080/15326340802427497).

![https://user-images.githubusercontent.com/4745789/99894937-fddc4380-2cac-11eb-8a73-a4dc5c490d2b.png](https://user-images.githubusercontent.com/4745789/99894937-fddc4380-2cac-11eb-8a73-a4dc5c490d2b.png)

Israeli Queues are a variation of [Priority Queues](https://en.wikipedia.org/wiki/Priority_queue) where instead of associating priority with the element to be enqueued, the priority is implicitly derived using the "friend" element and it joins right at the back end of the group that the friend belongs to. The function signature of the enqueue operation is as shown below, while other operations like `dequeue` and `peek` remains fairly similar.

```c
// Enqueues the element `e`, a friend of element `f`,
// into the queue `q`.
void enqueue(israeli_queue * q, element * e, element * f);
```

## How could this help?

Every Data Structures is designed to solve a niche use case efficiently and Israeli Queues are no different as they prove to be super-efficient where one could batch and process similar elements or where the *set-up* cost for a task is high.

Consider a system where a queue is used to hold up heterogeneous tasks and there is a single machine taking care of processing. Now if some of these tasks are similar and have a high *set-up or preparation cost*, for example downloading large metafiles, or spinning up a parallel infrastructure, or even setting up persistent connections with device farms, queuing them closer and processing them sequentially or in batch helps in reducing redundant processing and computation by promoting reuse.

## Issue of starvation

By enqueuing elements in between Israeli Queues reduces redundant processing, but by doing that it makes itself vulnerable to the classical case of starvation. Elements stuck at the rear end of the list could potentially starve for longer durations if elements having "friends" in the queue keep coming in at high frequency.

The original implementation of Israeli Queues suggests batch processing where instead of processing tasks one at a time, it processes a batch (a group of friends) in one go. This proves to be super-handy when the time required to processes a single task is much lower than the set-up cost for it.

## Implementation Guidelines

The best way to implement Israeli Queues is by using a [Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list) with a bunch of pointers pointing to the head and tail of groups within it. Insertion to an existing group happens at the tail of it while if the element has no friend element, then it goes at the tail end of the list and forms its own group.

A constraint that could be added during implementation is that the friend element should always be the leader (head) element of the group. Details of the implementation could be tweaked so long the core concept remains unaltered.

# The original use case of Israeli Queues

Israeli Queues were the outcome of a problem statement dealing with Polling Systems. Polling System usually contains `N` queues `Q1`, `Q2`, ..., `Qn` where the processing unit visits each queue in cyclic order processing one element at a time i.e. `Q1`, `Q2`, ..., `Qn`, `Q1`, `Q2`, ..., `Qn`, etc.

When the server attends a queue instead of processing just one element from it, it processes the entire batch present in the queue utilizing the setup-cost efficiently assuming that time to process an element from a queue is much lesser than the set-up cost.

# References

- [Polling with batch service](https://pure.tue.nl/ws/files/2152975/632939.pdf)
- [The Israeli Queue with priorities](http://www.math.tau.ac.il/~uriy/Papers/IQ-with-Priorities.pdf)
- [Israeli Queues: Exploring a bizarre data structure](https://rapidapi.com/blog/israeli-queues-exploring-a-bizarre-data-structure/)
