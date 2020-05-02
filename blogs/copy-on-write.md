Copy-On-Write, abbreviately referred as CoW, is a semantic that suggests how to efficiently create copies of resources when the intention is to not let the updates made in the copied instance be visible to the original instance. The resource to be copied could be anything, a in-memory page, database disk block, an item in data structure or the entire data structure.

A naive way to create such copies is by deep copying the resource. Deep-copying copies all the immediate pages along with all the other remote resources that are referenced within those pages. This makes deep-copying a very heavy operation consuming a lot of Memory and CPU cycles.

CoW is an alternate to this strategy in which a instead of creating a deep copy of a modifiable resource, everything is just copied by reference and before making the modification a deep copy of that particular chunk/resource is made and changes are applied. To gain a deeper understanding we see how CoW fares while copying a [Binary Tree](https://en.wikipedia.org/wiki/Binary_tree).

# Copy-on-write on a Binary Tree
Given a Binary Tree `A` we create a copy of `B` such that any modifications by `A` is not visible to `B` and any modifications by `B` are not visible to `A`. Naive way is to copy and clone all the nodes of the tree and let `B` now points to root of this new tree, as illustrated in the diagram below. Any modifications made to either tree will not be visible to the other because their entire space is mutually exclusive.

![Deep Copying a Binary Tree](https://user-images.githubusercontent.com/4745789/80859895-b3986400-8c81-11ea-9ebe-829540df77d5.png)

Copy-on-Write semantics suggest an optimistic approach where `B` instead of pointing to the cloned `A`, shares the same reference as `A` which means it also points to the exact same tree as `A`. But if both variables point to the same tree, how do we ensure isolation?

The Copy-on-Write semantics kick in when any modification happens. Say in tree `B` we change the value of node `2` to `9`, since we do not want tree `A` to see the change, instead of copying entire tree, only the path from the updated node till the root is cloned, keeping all other pointers refereces same, and now `B` points to this new root.

![Copy-on-Write a Binary Tree](https://user-images.githubusercontent.com/4745789/80869877-7606fb80-8cc0-11ea-8a9b-2b7312a59f11.png)

Copy on write is just a semantic, the implementation of this semantic depends on the data structure and the usecase. CoW with trees could be implemented as shown above, for LinkedList things are very similar to Trees becoase everything is just a pointer. In arrays 

# Why should we Copy-on-Write
Copy-on-Write is a wonderful way to save 
the copy operation is deferred to the first write
it is possible to significantly reduce the resource consumption of unmodified copies, while adding a small overhead to resource-modifying operations
when traversal operations vastly outnumber mutations

 - removes the need of deep copying
 - say if copy something and do not modify at all, out deep copy efforts are a loss
 - efficient rollbacks

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
Point in time snapshots

## CoW in Data Structures
Persistent Data Structures is hwere 

## CoW in Real World applications
Document Versioning

## CoW in Time Travel

# Why shouldn't we Copy-on-Write

 - if you operations are write heavy then CoW has a huge overhead.

# References
 - http://schd.ws/hosted_files/buildstuff14/96/20141120-BuildStuff-Lightning.pdf
 - https://stackoverflow.com/questions/35279756/what-is-special-about-internal-design-of-lmdb
 - [Fork Exec Pattern](https://en.wikipedia.org/wiki/Fork%E2%80%93exec)
