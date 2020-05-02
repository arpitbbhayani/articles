Copy-On-Write, abbreviately referred as CoW, is a semantic that suggests how to efficiently create copies of resources when the intention is to not let the updates made in the copied instance be visible to the source instance. The resource to be copied could be anything, a in-memory page, database disk block, an item in data structure or the entire data structure.

A naive way to create such copies is by deep copying the resource. Deep-copying copies all the immediate pages along with all the other remote resources that are referenced within those pages. This makes deep-copying a very heavy operation consuming a lot of Memory and CPU cycles.

CoW is an alternate to this strategy in which a instead of creating a deep copy of a modifiable resource, everything is just copied by reference and when the modification is to be made then the deep copy of that particular chunk is made and changes are applied.

# What exactly is Copy-on-write semantic
LinkedList example

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
