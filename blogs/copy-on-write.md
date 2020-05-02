Copy-On-Write, abbreviately referred as CoW, is a semantic that suggests how to efficiently create copies of resources when the intention is to not let the updates made in the copied instance be visible to the source instance. The resource to be copied could be anything, a in-memory page, database disk block, an item in data structure or the entire data structure.

A naive way to create such copies is by deep copying the resource. Deep-copying copies all the immediate pages along with all the other remote resources that are referenced within those pages. This makes deep-copying a very heavy operation consuming a lot of Memory and CPU cycles.

CoW is an alternate to this strategy in which a instead of creating a deep copy of a modifiable resource, everything is just copied by reference and before making the modification a deep copy of that particular chunk/resource is made and changes are applied. To gain a deeper understanding we see how CoW fares while copying a [Doubly LinkedList](https://en.wikipedia.org/wiki/Doubly_linked_list).

# Copy-on-write on a Doubly LinkedList
Given a Doubly LinkedList `A` we create a copy of `B` such that any modifications by `A` is not visible to `B` and any modifications by `B` are not visible to way. Naive way was to copy and clone all the nodes of the LinkedList and let `B` now points to head of this new list.

![Deep Copying a Doubly LinkedList](https://user-images.githubusercontent.com/4745789/80857167-978ac780-8c6d-11ea-9fc5-238753391eb2.png)


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
