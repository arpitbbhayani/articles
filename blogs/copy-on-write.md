Copy-On-Write, abbreviately referred as CoW, is a semantic that suggests how to efficiently create copies of resources when the intention is to not let the updates made in the copied instance be visible to the source instance. The resource to be copied could be anything, ranging from a memory oage, database disk block, an item in data structure or a data structure as a whole.

A naive way to create such copies is by deep copying the resource and this deep copying copies all the immediate pages to be copied along with all the remote references that are pointed as well. Thus deep copying is a very heavy operation which consumes a ton of CPU cycles and memory blocks. CoW is an alternative to deep copying.

in which a instead of creating a deep copy of a modifiable resource, it is copied by reference but when the resource is to be modified then the copy is made and updates are applied.

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
