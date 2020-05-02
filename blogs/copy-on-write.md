Copy-On-Write, abbreviately referred as CoW, is a semantic that suggests how to efficiently create copies of resources when the intention is to not let the updates made in the copied instance be visible to the source instance. The resource to be copied could be anything, a in-memory page, database disk block, an item in data structure or the entire data structure.

A naive way to create such copies is by deep copying the resource. Deep-copying copies all the immediate pages along with all the other remote resources that are referenced within those pages. This makes deep-copying a very heavy operation consuming a lot of Memory and CPU cycles.

CoW is an alternate to this strategy in which a instead of creating a deep copy of a modifiable resource, everything is just copied by reference and before making the modification a deep copy of that particular chunk/resource is made and changes are applied. To gain a deeper understanding we see how CoW fares while copying a [Binary Tree](https://en.wikipedia.org/wiki/Binary_tree).

# Copy-on-write on a Binary Tree
Given a Binary Tree `A` we create a copy of `B` such that any modifications by `A` is not visible to `B` and any modifications by `B` are not visible to `A`. Naive way is to copy and clone all the nodes of the tree and let `B` now points to root of this new tree, as illustrated in the diagram below. Any modifications made to either tree will not be visible to the other because their entire space is mutually exclusive.

![Deep Copying a Binary Tree](https://user-images.githubusercontent.com/4745789/80859895-b3986400-8c81-11ea-9ebe-829540df77d5.png)

Copy-on-Write semantics suggest an optimistic approach where `B` instead of pointing to the cloned `A`, shares the same reference as `A` which means it also points to the exact same tree as `A`. But if both variables point to the same tree, how do we ensure isolation?

The Copy-on-Write semantics kick in when any modification happens. Say in tree `B` we change the value of node `2` to `9`, since we do not want tree `A` to see the change, instead of copying entire tree, only the path from the updated node till the root is cloned, keeping all other pointers refereces same, and now `B` points to this new root.

![Copy-on-Write a Binary Tree](https://user-images.githubusercontent.com/4745789/80869877-7606fb80-8cc0-11ea-8a9b-2b7312a59f11.png)

# Why should we Copy-on-Write

# CoW in action
Each deserves its own essay.

## CoW in Operating Systems

## CoW in Databases

## CoW in Data Structures

## CoW in Languages
Deepcopy

## CoW in Data Engineering
Point in time snapshots

## CoW in Applications
Document Versioning

# References
 - http://schd.ws/hosted_files/buildstuff14/96/20141120-BuildStuff-Lightning.pdf
 - https://stackoverflow.com/questions/35279756/what-is-special-about-internal-design-of-lmdb
