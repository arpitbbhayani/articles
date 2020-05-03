Copy-On-Write, abbreviately referred to as CoW suggests deferring the copy process until the first modification. A resource is usually copied when we do not want the changes made in either resource to be visible to the other. A resource here could be anything - an in-memory page, a database disk block, an item in a structure or even the entire data structure.

CoW suggests that we first copy by reference and let both instances point to the same resource and before the first modification we clone the original resource and then apply the updates. In a gist CoW suggests we defer the process of copying until the first modification is about to be made.

# Deep copying
The process of creating a pure clone of the resource is called [Deep Copying](https://en.wikipedia.org/wiki/Object_copying#Deep_copy) and it copies not only the immediate resource but also all the remote resources that are referenced within it. Thus if we were to deep copy a [Linked List](https://en.wikipedia.org/wiki/Linked_list) we do not copy the head pointer, rather we clone all the nodes of the list and create an entirely new list from the original one. A C++ function deep copying a Linked List is as illustrated below

```cpp
struct node* copy(struct node *head) {
    if (!head) {
        return NULL;
    }

    struct node *nhead = (struct node *) malloc(sizeof(struct node))
    nhead->val = head->val;

    struct node *p = head;
    struct node *q = nhead;

    while(p -> next) {
        q -> next = (struct node *) malloc(sizeof(struct node));
        q -> next -> val = p -> next -> val;
        p = p -> next;
        q = q -> next;
    }

    return nhead;
}
```

![deep copying a linked list](https://user-images.githubusercontent.com/4745789/80907205-76d87580-8d32-11ea-88a8-153a94d92d72.png)

Going by the details, we understand that deep copying is a very memory-intensive operation for any resource.

# Why should we Copy-on-Write
Copy-on-Write, as established earlier, suggests we defer the copy operation until the first modification is requested. The approach suits the best when the traversal and access operations vastly outnumber the mutations. CoW has anumber of advantages, some of them are

## Getting things done quickly
By having a CoW technique, the process need not wait for the deep copy to happen, instead it could directly proceed to the next phase by doing a copy-by-reference. This is particularly beneficial during `fork` system call.

`fork` system call creates child process which in turn copies entire memory space of parent. If during this `fork` call if the parent's space is huge and we deep copy, the time taken to create child process will shoot up. Hence instead by having a CoW we would just copy-by-reference and child could point to the same space as parent until the child makes some modification to the space.

## Why deep copy if there are no modifications
CoW gives us an optimistic way to manage memory. One peculiar property that CoW exploits is how before any modification to the copied instance, both the original and copied resource are exactly the same.

The readers, thus, cannot distinguish if it is reading from original resource or the copied one. Hence deep copy and copy-by-reference would look and feel exactly the same to a reader. The things change when the first modification is made to the copied instance and thats where, readers of corresponding resource would see things differently, and hence just before that we copy the resource.

If the copied resource is never modified, having a CoW approach would make things super performant. When there are no modifications to be made, the original and copied resoucrce will be exactly same, hence by putting CoW we can avoid deep-copy altogether and let the both the processes share the same location.

it saves a lot of Memory and computations.

THis is usually the case when the `fork` system call is made to create child process. [fork-exec-wait](https://en.wikipedia.org/wiki/Fork%E2%80%93exec) is a very common pattern in operating systems; where a child process is forked and immedeatly it executes a program replacing the entire copied parent space. Here since the child do not intend to modify its program space, inherited from parent, and simply replace it with the new program, bu having CoW makes sene. We have a lot of efforts.

## No Locks Required
One major benefit we get from CoW is that it removes the need of Locks altogether. Since on every write we are creating a new copy of the resource there are no in-place updates. Hence 

# Implementing CoW
CoW is just a technique and it tells us what and not how. The implementation is all in the hands of the system and depending on the type of resource bing CoWed the implementation details differ.

Naive way is how we deep copy a list. But we can do a lot better.

To gain a deeper understanding we see how enfficiently could be make CoW for a Binary Tree [Binary Tree](https://en.wikipedia.org/wiki/Binary_tree).

## Effieicnt Copy-on-write on a Binary Tree
Given a Binary Tree `A` we create a copy `B` such that any modifications by `A` is not visible to `B` and any modifications by `B` are not visible to `A`. Naive way is to copy and clone all the nodes of the tree and let `B` now points to root of this new tree, as illustrated in the diagram below. Any modifications made to either tree will not be visible to the other because their entire space is mutually exclusive.

![Deep Copying a Binary Tree](https://user-images.githubusercontent.com/4745789/80859895-b3986400-8c81-11ea-9ebe-829540df77d5.png)

Copy-on-Write semantics suggest an optimistic approach where `B` instead of pointing to the cloned `A`, shares the same reference as `A` which means it also points to the exact same tree as `A`. Now say we modify the node `2` in tree `B` and change its value to `9`. As per CoW now we need to clone the tree and then apply the modifications.

Again a naive way would be to clone the entire tree and then make the necessary modifications, but observing closely we find that a lot of pointers could be reused and hence a better approach would be to only copy the path from the updated node till the root, keeping all other pointers refereces same, and now `B` points to this new root, as shown in the illustration.

![Copy-on-Write a Binary Tree](https://user-images.githubusercontent.com/4745789/80869877-7606fb80-8cc0-11ea-8a9b-2b7312a59f11.png)

Copy on write is just a semantic, the implementation of this semantic depends on the data structure and the usecase. CoW with trees could be implemented as shown above, for Linked List things are very similar to Trees becoase everything is just a pointer. In arrays 

# CoW in action
In this section we see how Copy-on-Write semantics finds its use in a variety of fields and branches like Operating Systems, Databases, and even Time Travel.

## CoW in Databases
Database is structured with BTrees.
Locks could be avoided. Readers will not see things updating by a writer. 
No need of locks
attomic compare and swap.

## CoW in Data Engineering
Database in in-conssitent state, going back in time and restore the db to its last
known stable state. with CoW we can take our DB to any version in past.
Point in time snapshots

## CoW in Data Structures
Persistent Data Structures is hwere 
There are data strucutes that upon updation creates a new copy instead of making an
in-place update. For example: adding a new element in array, we create a new copy.
Why such data strutures are needed?

## CoW in Real World applications
While using a collaborative doument editor like, Google Doc, one malicious user with write access to the
document could just erase entire content of the document.
Thus we need a way to revert the changes made by the malicous user and user an earlier revision of the
document that we know was last stable and proper version.

Deepcopying document on every single update is not a good option as it would require the tool to create new copies on every update, say every second. Which is infeasible solution in terms of storage requirements.

CoW semantic could help in this as when the document is updated only some part of the document is updated after the last save, thus CoW is ideal for such scenarious.

## CoW in modelling Time Travel
Whenever Flash, a DC Superhero, goes back in time to fix something, he creates a new time line. This new timeline
has all of its events fareing in a different way depending on which event was interefered with.

modelling multiple timelines i.e. parallel universes could done with the help of CoW semantics, where instead
of creating deep copy of the entire universe, we apply CoW semantics and store references to unchanged items
while copying the chunks that changed.

# Why shouldn't we Copy-on-Write

 - if you operations are write heavy then CoW has a huge overhead.

# References
 - http://schd.ws/hosted_files/buildstuff14/96/20141120-BuildStuff-Lightning.pdf
 - https://stackoverflow.com/questions/35279756/what-is-special-about-internal-design-of-lmdb
 - [Fork Exec Pattern](https://en.wikipedia.org/wiki/Fork%E2%80%93exec)
