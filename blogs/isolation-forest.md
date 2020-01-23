Anomaly detection is identification of something that is not "normal"; the definition of what "normal" is, depends on what is observed and its properties. In this article we go in-depth of a popular unsupervised anomaly detection algorithm named [Isolation Forest](https://cs.nju.edu.cn/zhouzh/zhouzh.files/publication/icdm08b.pdf). This algorithm beautifully exploits the properties and characteristics of anomalies and keeps it independent of data distributions, and ...

### Why should we detect anomalies?

 - anomalies in credit card transactions could signify fraudulent use
 - anomalous spot in an astronomy image could indicate a new star
 - anomalous network traffic pattern could stand for an attack or an unauthorized access

# Characteristics of anomalies

Since anomalies deviates from normal it means they are few in numbers (minority) and have attribute values that are very different from those of normal. The paper nicely puts it as: anomalies are **few and different**. These characteristics of anomalies make them more susceptible to isolation than normal points.

# The usual approach for detecting anomalies

The existing models train to see what constitutes "normal" and then considers everything that does not conform to this definition as anomalies. To name a few methods that does this, and very widely used, are:

 - statistical methods - , , ,
 - classification-based methods - , , ,
 - clustering-based methods - , , ,

Since these methods are not optimized detect anomalies, instead are optimized to find normal instances, the results of anomaly detection contains too many false positives or might detect too few anomalies. Many of these methods are computationally complex and hence suits low dimensional and/or small sized data. Isolation Forest algorithm fixes both of the above issues and provides highly efficient and accurate way to detect anomalies.

# The algorithm
Now we take a look at the algorithm, what it does, how it does and the math behind it. Fasten your seatbelts; it's going to be a bumpy ride.

## The core principle
The core of the algorithm is to "isolate" anomalies by creating a decision tree on points over a particular attribute. Since anomalies are susceptible to isolation, they isolate closer to the root while normal points isolate at deeper levels.

DIAGRAM goes here.

In the diagram above you could see how anomalies are isolated closer to the root of the tree; and we see how the principle explicitly isolates anomalies rather than profiles normal instances.

Since by creating one decision tree we cannot for sure say that a point is an anomaly, this process is repeated multiple times and split happen over random attribute and attribute value. Thus a set of tree is maintained (forest) and average level of each point across forest gives its likeliness to be isolated. The true anomalous points will more often than note have lower level/depth/height and hence this method is called Isolation Forest method.

## Construction of decision tree

The decision tree is constructed by splitting the given points/instances over a split value such that the instances whose corresponding attribute value is smaller than the split value goes left and the others go right; and the process is continued recursively until the tree is fully constructed; which means all nodes contain just 1 element.

There are two types of node in the decision tree:

### Internal Node

Internal nodes are non-leaf and contains data points/instances and the split condition; depending on the split condition it will be parent to two sub-trees or two external nodes.

DIAGRAM

### External Node

External nodes are leaf nodes that could not be split further and reside at the bottom of the tree. An external node will always have a sibling node (either internal or external).

DIAGRAM

### Optimizing decision tree construction

Since anomalies are susceptible to isolation and have a tendency to reside closer to the root of the decision tree, we could just construct the decision tree till it reaches a certain height. This height is the height post which which we are sure that there could not be any anomalies. In order to estimate this height we compare this decision tree to a BST.

The pseudo-code for tree construction looks something like this.

```py
def construct_tree(X, current_height, max_height):
  """The function constructs a tree/sub-tree on points X.

  current_height: represents the height which the tree will exist to the root.
  max_height: the max height of the tree.

  The current_height and max_height only exists to make algorithm efficient
  as we assume that no anomalies exists at depth >= max_height.
  """
  if current_height >= max_height:
    # here we are sure that no anomalies exist hence we
    # directly construct the external node.
    return new_external_node(X)

  # pick any attribute at random.
  attribute = get_random_attribute(X)

  # for set of inputs X, for the tree we get a random value
  # for the chosen attribute. preferably around the median.
  split_value = get_random_value(max_value, min_value)

  # split X instances based on `split_values` into Xl and Xr
  Xl = filter(X, lambda x: X[attribute] < split_value)
  Xr = filter(X, lambda x: X[attribute] >= split_value)

  # build an internal node with its left subtree created from Xl
  # and right subtree created from Xr, recursively.
  return new_internal_node(
    left=construct_tree(Xl, current_height + 1, max_height),
    right=construct_tree(Xr, current_height + 1, max_height),
    split_attribute=attribute,
    split_value=split_value,
  )
```

## Constructing the forest

The pseudo-code for tree construction looks something like this.

```py
def construct_forest(X, trees_count, subsample_count):
  """The function constructs a forest from given inputs/data points X.
  """
  forest = []
  for i in range(0, trees_count):
    # compute max_height to which we construct the decision tree.
    # we assume that post this height/level we will not not discover
    # any anomalies.
    max_height = math.ceil(math.log2(subsample_count))

    # create a sample with cardinality of `subsample_count` from X
    X_sample = get_sample(X, subsample_count)

    # construct the decision tree from the sample
    tree = construct_tree(X_sample, 0, max_height)

    # add tree to the forest
    forest.append(tree)

  return forest
```

## Finding the anomalies



----

There are only two variables in thismethod: the number of trees to build and the sub-samplingsize.
itonly requires a small sub-sampling size to achieve high de-tection performance with high efficiency


partitioning ofinstances are repeated recursively until all instances are iso-lated
This random partitioning produces noticeable shorterpaths for anomalies since (a) the fewer instances of anoma-lies result in a smaller number of partitions – shorter pathsin a tree structure, and (b) instances with distinguishableattribute-values are more likely to be separated in early par-titioning. Hence, when a forest of random trees collectivelyproduce shorter path lengths for some particular points, thenthey are highly likely to be anomalies.

partitions are generated byrandomly selecting an attribute and then randomly selecting
a split value between the maximum and minimum values ofthe selected attribute.

Since recursive partitioning can berepresented by a tree structure, the number of partitions re-quired to isolate a point is equivalent to the path length fromthe root node to a terminating node. In this example, thepath length ofxiis greater than the path length ofxo.

### The binary search tree
Since each partition is randomly generated, individualtrees are generated with different sets of partitions. We av-erage path lengths over a number of trees to find the ex-pected path length.
Using1000trees, the average path lengths ofxoandxiconverge to4.02and12.82respectively. It showsthat anomalies are having path lengths shorter than normalinstances.

Isolation Tree.LetTbe a node of an isola-tion tree.Tis either an external-node with no child, or aninternal-node with one test and exactly two daughter nodes(Tl,Tr). A test consists of an attributeqand a split valuepsuch that the testq < pdivides data points intoTlandTr.

An iTree is aproper binary tree where each node in the tree has exactly zero or two daughternodes.

when an iTree is fully grown, inwhich case the number of external nodes isnand the num-ber of internal nodes isn−1; the total number of nodesof an iTrees is2n−1; and thus the memory requirement isbounded and only grows linearly with n.

### Scoring

Path Lengthh(x)of a pointxis measured bythe number of edgesxtraverses an iTree from the root nodeuntil the traversal is terminated at an external node

the estimation of aver-ageh(x)for external node terminations is the same as the unsuccessful search in BST.
Given adata set ofninstances, Section 10.3.3 of [9] gives the aver-age path length of unsuccessful search in BST as:c(n) = 2H(n−1)−(2(n−1)/n),(1)whereH(i)is the harmonic number and it can be estimatedbyln(i)+0.5772156649(Euler’s constant). Asc(n)is theaverage ofh(x)givenn, we use it to normaliseh(x). Theanomaly scoresof an instancexis defined as:s(x,n) = 2−E(h(x))c(n),(2)whereE(h(x))is the average ofh(x)from a collection ofisolation trees. In Equation (2):•whenE(h(x))→c(n),s→0.5;•whenE(h(x))→0,s→1;•and whenE(h(x))→n−1,s→0.

sis monotonic toh(x). Figure 2 illustrates the relationshipbetweenE(h(x))ands, and the following conditions ap-plied where0< s≤1for0< h(x)≤n−1. Using theanomaly scores, we are able to make the following assess-ment:•(a) if instances returnsvery close to1, then they aredefinitely anomalies,•(b) if instances havesmuch smaller than 0.5, then theyare quite safe to be regarded as normal instances, and•(c) if all the instances returns≈0.5, then the entiresample does not really have any distinct anomaly

s≥0.6, which are potential anomalies

## Why this algorithm?

build partial models and exploit sub-sampling to anextent that is not feasible in existing methods
a large part of an iTree that isolates normal points isnot needed for anomaly detection; it does not need tobe constructed
iForest utilizes no distance or density measures to de-tect anomalies. This eliminates major computationalcost of distance calculation in all distance-based meth-ods and density-based methods.
iForest has a linear time complexity with a lowconstant and a low memory requirement

### Details

Since iForest does not need to iso-late all of normal instances – the majority of the trainingsample,iForest is able to work well with a partial modelwithout isolating all normal points and builds models usinga small sample size.

isolation method works best when thesampling size is kept small

large sampling size reducesiForest’s ability to isolate anomalies as normal instances caninterfere with the isolation process and therefore reducesits ability to clearly isolate anomalies.

### Swamping and Masking

Swamping: wrongly identifying normal instances as anomalies
Whennormal instances are too close to anomalies, the number ofpartitions required to separate anomalies increases – whichmakes it harder to distinguish anomalies from normal in-stances

Masking is the existence of too many anomaliesconcealing their own presence. When an anomaly cluster islarge and dense, it also increases the number of partitionsto isolate each anomaly.

The unique characteristic ofisolation trees allows iForest to build a partial model bysub-sampling which incidentally alleviates the effects ofswamping and masking. It is because: 1) sub-sampling con-trols data size, which helps iForest better isolate examplesof anomalies and 2) each isolation tree can be specialised,as each sub-sample includes different set of anomalies or even no anomaly.

### Other reasons

https://blog.easysol.net/using-isolation-forests-anamoly-detection/

## The Algorithm
Anomaly detection using iForest is a two-stage process.The first (training) stage builds isolation trees using sub-samples of the training set.  The second (testing) stagepasses the test instances through isolation trees to obtainan anomaly score for each instance

### Training
In the training stage, iTrees are constructed by recur-sively partitioning the given training set until instances areisolated or a specific tree height is reached of which resultsa partial model. Note that the tree height limitlis automat-ically set by the sub-sampling sizeψ:l=ceiling(log2ψ) which is approximately the average tree heigh.

The ra-tionale of growing trees up to the average tree height is thatwe are only interested in data points that have shorter-than-average path lengths, as those points are more likely to beanomalies.

### Evaluation

In the evaluating stage, an anomaly scoresis derivedfrom the expected path lengthE(h(x))for each test in-stance.E(h(x))are derived by passing instances througheach iTree in an iForest. UsingPathLengthfunction, asingle path lengthh(x)is derived by counting the numberof edgesefrom the root node to a terminating node as in-stancextraverses through an iTree. Whenxis terminatedat an external node, whereSize >1, the return value iseplus an adjustmentc(Size). The adjustment accounts foran unbuilt subtree beyond the tree height limit.

...

## Advantages

One of the important challenges in anomaly detection ishigh dimensional data. For distance-based methods, everypoint is equally sparse in high dimensional space — render-ing distance a useless measure. For iForest, it also suffersfrom the same ‘curse of dimensionality’
Forest hasa significant advantage in processing time

The implication of using a small sub-sample size is thatone can easily host an online anomaly detection system with minimal memory footprint

# Conclusion

This is the first article in series of Algorithms.