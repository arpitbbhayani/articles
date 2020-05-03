Copy-On-Write, abbreviately referred as CoW, is a semantic that suggests to defer the copy process until the first modification. A resource is usually copied when we do not want the changes made in either to be visible to the other. A resource here could be anything - an in-memory page, a database block, an item in a structure or even the entire data structure.

CoW suggests that we first copy by reference and let both instances point to the same resource and just before the first modification we clone the original resource and then apply the modification. Thus CoW suggets we defer the process of copying until the first modification is about to be made.

# Why should we Copy-on-Write
CoW gives a significant improvement while creating the first copy of any resource. Since the first copy is just a copy-by-reference it is lightning fast. CoW also does really well in cases where the copied resources are never modified. Deep-copying a resource that is never modified is a waste of memory and CPU cycles, using CoW hus saves these efforts.

CoW is just a semantic and it tells what and not how. Thus the implementation is all in the hands of the system and depending on the type of resource bing CoWed the implementation details differ.


Copy-on-Write is a wonderful way to save 
the copy operation is deferred to the first write
it is possible to significantly reduce the resource consumption of unmodified copies, while adding a small overhead to resource-modifying operations
when traversal operations vastly outnumber mutations

 - removes the need of deep copying
 - say if copy something and do not modify at all, out deep copy efforts are a loss
 - efficient rollbacks


To gain a deeper understanding we see how enfficiently could be make CoW for a Binary Tree [Binary Tree](https://en.wikipedia.org/wiki/Binary_tree).

# Deep copying
The process of creating a pure clone of the reousce is called Deep-Copying and it copies not only the immediate pages but also all the remote resources that are referenced within those pages. Going by the details of deep-copying we know that deep-copying a resource is a very memory intensive process.

Creating a deep copy of a linkedlist

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

# Effieicnt Copy-on-write on a Binary Tree
Given a Binary Tree `A` we create a copy `B` such that any modifications by `A` is not visible to `B` and any modifications by `B` are not visible to `A`. Naive way is to copy and clone all the nodes of the tree and let `B` now points to root of this new tree, as illustrated in the diagram below. Any modifications made to either tree will not be visible to the other because their entire space is mutually exclusive.

![Deep Copying a Binary Tree](https://user-images.githubusercontent.com/4745789/80859895-b3986400-8c81-11ea-9ebe-829540df77d5.png)

Copy-on-Write semantics suggest an optimistic approach where `B` instead of pointing to the cloned `A`, shares the same reference as `A` which means it also points to the exact same tree as `A`. Now say we modify the node `2` in tree `B` and change its value to `9`. As per CoW now we need to clone the tree and then apply the modifications.

Again a naive way would be to clone the entire tree and then make the necessary modifications, but observing closely we find that a lot of pointers could be reused and hence a better approach would be to only copy the path from the updated node till the root, keeping all other pointers refereces same, and now `B` points to this new root, as shown in the illustration.

![Copy-on-Write a Binary Tree](https://user-images.githubusercontent.com/4745789/80869877-7606fb80-8cc0-11ea-8a9b-2b7312a59f11.png)

Copy on write is just a semantic, the implementation of this semantic depends on the data structure and the usecase. CoW with trees could be implemented as shown above, for LinkedList things are very similar to Trees becoase everything is just a pointer. In arrays 

# CoW in action
In this section we see how Copy-on-Write semantics finds its use in a variety of fields and branches like Operating Systems, Databases, and even Time Travel.

## CoW in Operating Systems
`fork()` is one for the most important System Call in a Operating SYstem. It is responsible of creating a new child process. The newly created child process is a spitting copy of the parent process (the one who called `fork`). Typically this child process does not modify any memory and immedeatly executes a new process replacing the address space entirely.

Hence if the `fork`, while creating the child process, deep copies the entire address space and the child process does not use any of it, the expensive deepcopy is a total waste. Hence it makes sense to have a Copy-on-Write semantic where the deep copy is deferred until the first write. This way we `fork` creates the new child process faster and has minimal memory overhead.

fork-exec-wait pattern

A common programming pattern is to call fork followed by exec and wait. The original process calls fork, which creates a child process. The child process then uses exec to start execution of a new program. Meanwhile the parent uses wait (or waitpid) to wait for the child process to finish. See below for a complete code example.

```cpp
#include <stdio.h>
int main( void ) {
	char *argv[3] = {"Command-line", ".", NULL};
	int pid = fork();
	if ( pid == 0 ) {
        // The child process replacing the entire address space of the parent
		execvp( "find", argv );
	}
	wait(2);
	return 0;
}
```

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

## CoW in Time Travel
Whenever Flash, a DC Superhero, goes back in time to fix something, he creates a new time line. This new timeline
has all of its events fareing in a different way depending on which event was interefered with.

modelling multiple timelines i.e. parallel universes could done with the help of CoW semantics, where instead
of creating deep-copy of the entire universe, we apply CoW semantics and store references to unchanged items
while copying the chunks that changed.

# Why shouldn't we Copy-on-Write

 - if you operations are write heavy then CoW has a huge overhead.

# References
 - http://schd.ws/hosted_files/buildstuff14/96/20141120-BuildStuff-Lightning.pdf
 - https://stackoverflow.com/questions/35279756/what-is-special-about-internal-design-of-lmdb
 - [Fork Exec Pattern](https://en.wikipedia.org/wiki/Fork%E2%80%93exec)
