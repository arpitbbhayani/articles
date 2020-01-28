Anomaly detection is the identification of something that could be stated as "normal"; the definition of what "normal" is, depends on the phenomenon that is being observed and the properties it bears. In this article, we go in-depth of an unsupervised anomaly detection algorithm called [Isolation Forest](https://cs.nju.edu.cn/zhouzh/zhouzh.files/publication/icdm08b.pdf). This algorithm beautifully exploits the characteristics of anomalies, keeping it independent of data distributions.

### Characteristics of anomalies
Since anomalies deviate from normal it implies that they are few in numbers (minority) and have attribute values that are very different from those of normal. The paper nicely puts it as: 'anomalies are **few and different**'. These characteristics of anomalies make them more susceptible to isolation than normal points and this algorithm puts it to good use.

# The usual approach for detecting anomalies
The existing models train to see what constitutes "normal" and then considers everything that does not conform to this definition as anomalies. Almost every single algorithm has its own way of defining what is normal and then loops to data points and filters out those who do not satisfy the constraint. These methods usually exploit of the following methods to define what's normal,

 - statistical methods
 - classification-based methods
 - clustering-based methods

### The issue with the usual approach
Since these methods are not optimized to detect anomalies, instead are optimized to find normal instances, the results of anomaly detection either contains too many false positives or might detect too few anomalies.

Many of these methods are computationally complex and hence suit low dimensional and/or small-sized data.

Isolation Forest algorithm fixes both of the above issues and provides a highly efficient and accurate way to detect anomalies.

# The algorithm
Now we take a look at the algorithm, what it does, how it does and the math behind it. Fasten your seat belts, it's going to be a bumpy ride.

## The core principle
The core of the algorithm is to "isolate" anomalies by creating a decision tree on points over random attributes. The random partitioning produces noticeable shorter paths for anomalies since

 - fewer instances result in smaller partitions
 - distinguishable attribute values are more likely to be separated in early partitioning

Hence, when a forest of random trees collectively produces shorter path lengths for some particular points, then they are highly likely to be anomalies.

![Decision tree splits for normal points and anomalies](https://user-images.githubusercontent.com/4745789/73243800-804fc000-41ce-11ea-826f-14cbc407af99.png)

The diagram above shows the isolation pattern for normal points and anomalies. The number of splits (blue lines) happeneing to construct a decision tree are more in case of normal points and fewer for anomalies. These splits determine the edges to be traversed to reach the isolated node.

The process is repeated multiple times and split happens over random attribute and attribute value. The points that isolate closer to the root, more often than not are labeled as anomalies. Hence a set of trees (forest) is maintained and the average level of each point across forest gives its likeliness to be isolated. The true anomalous points will more often than note have lower height.

## Construction of decision tree
The decision tree is constructed by splitting the sub-sample points/instances over a split value such that the instances whose corresponding attribute value is smaller than the split value goes left and the others go right; and the process is continued recursively until the tree is fully constructed. The split value is selected at random between the minimum and maximum values of the selected attribute.

There are two types of node in the decision tree

DIAGRAM OF INTERNAL AND EXTERNAL NODES

### Internal Node

Internal nodes are non-leaf and contain data points/instances and the split condition; depending on the split condition it will be parent to two sub-trees or two external nodes.

### External Node

External nodes are leaf nodes that could not be split further and reside at the bottom of the tree. An external node will always have a sibling node (either internal or external).

## Why sub-sampling helps
The Isolation Forest algorithm works well when the trees are created, not from the entire dataset, but from a subsampled data set. This is contrary to almost all other techniques where every other technique thrievs on data and demands more of it for greater accuracy. Subsampling works wonders in this algorithm because normal instances can interfere with the isolation process by being a little closer to the actual anomalies. This is very evident from the diagram below.

DIAGRAM SHOWING SUBSAMPLING IMPORTANCE

### Optimizing decision tree construction

Since anomalies are susceptible to isolation and have a tendency to reside closer to the root of the decision tree, we could just construct the decision tree till it reaches a certain height and not split points further. This height is the height post which we are (almost) sure that there could not be any anomalies.

```py
def construct_tree(X, current_height, max_height):
  """The function constructs a tree/sub-tree on points X.

  current_height: represents the height which the tree will exist to the root.
  max_height: the max height of the tree.

  The current_height and max_height only exists to make algorithm efficient
  as we assume that no anomalies exist at depth >= max_height.
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

We get to choose the number of trees we want in the forest, there is no specific way to do this; but in general: more the merrier. Not only we get to choose the number of trees, but we also choose the number of nodes in each tree - sub-sample size. The algorithm requires a sub-sample to operate efficiently and yields a very high performance while doing so.

```py
def construct_forest(X, trees_count, subsample_count):
  """The function constructs a forest from given inputs/data points X.
  """
  forest = []
  for i in range(0, trees_count):
    # max_height is in fact the average height of the tree that would be
    # constructed from given points. This acts as max_height for the
    # construction because we are only interested in data points that have
    # shorter-than-average path lengths, as those points are more likely
    # to be anomalies.
    max_height = math.ceil(math.log2(subsample_count))

    # create a sample with cardinality of `subsample_count` from X
    X_sample = get_sample(X, subsample_count)

    # construct the decision tree from the sample
    tree = construct_tree(X_sample, 0, max_height)

    # add tree to the forest
    forest.append(tree)

  return forest
```

## Scoring the anomalies
Every anomaly detection algorithm has to score its data points/instances and quantify the confidence the algorithm has on its potential anomalies, and it should be bounded and comparable. In Isolation Forest, we know that anomalies always stay closer to the root, and this becomes our guiding and defining insight that will help us build a scoring function. Hence the anomaly score will a function of path length which is defined as

> Path Length `h(x)` of a point `x` is the number of edges `x` traverses from the root node.

As the maximum possible height of the tree grows by order of `n`, the average height grows by `log(n)` - this makes normalizing the scoring function a little tricky. To remedy this we use the insights from the structure of the decision tree. The decision tree has two types of nodes internal and external such that external has no child while internal is a parent to exactly two nodes - which means the decision tree is a proper binary tree and hence we conclude

> The average path length `h(x)` for external node termination is the same as the average path length of unsuccessful search in BST.

In a BST, an unsuccessful search always terminates at a `NULL` pointer and if we treat external node of the decision tree as `NULL` (of BST) then we could say that average path length of external node termination is same as average path length of unsuccessful search in BST (constructed only from internal nodes of the decision tree), and is given by

![BST unsuccessful search estimation](https://user-images.githubusercontent.com/4745789/73191802-198ac200-414e-11ea-9500-039483b6e780.png)

where `H(i)` is the [harmonic number](https://en.wikipedia.org/wiki/Harmonic_number) and it can be estimated by `ln(i) + 0.5772156649` ([Euler–Mascheroni constant](https://en.wikipedia.org/wiki/Euler%E2%80%93Mascheroni_constant)). `c(n)` is the average of `h(x)` given `n`, we use it to normalize `h(x)`.

To understand the derivation in detail refer
 - [IIT KGP, Algorithms, Lecture Notes - Page 7](https://cse.iitkgp.ac.in/~pb/algo-1-pb-10.pdf)
 - [What is real big-O of search in BST?](https://www.cs.csustan.edu/~john/classes/previous_semesters/cs3100_datastructures/2000_04_Fall/Examples/Trees/averageSearchInBST.html)
 - [CMU CMSC 420: Lecture 5 - Slide 13](https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/trees.pdf)
 - [CISE UFL: Data Structures, Algorithms, & Applications - 1st Proof](https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c18/e47.htm)

The anomaly score of an instance `x` is defined as

![scoring function](https://user-images.githubusercontent.com/4745789/73192432-075d5380-414f-11ea-86dc-ae6acda7b7d4.png)

where `E(h(x))` is the average of `h(x)` from a collection of isolation trees. From the scoring function defined above, we could deduce that if

 - the score is very close to 1, then they are definitely anomalies
 - the score is much smaller than 0.5, then they are quite safe to be regarded as normal instances, and
 - all the instances return around 0.5, then the entire sample does not really have any distinct anomaly

GRAPH OF VARIATION OF score with `E(h(x))`

## Evaluating anomalies

In the evaluation stage, an anomaly score is derived from the expected path length `E(h(x))` for each test instance. Using `get_path_length` function (pseudocode below), a single path length `h(x)` is calculated by traversing through the decision tree.

If iteration terminates at an external node where `size > 1` then the return value is `e` (edge count traversed till current node) plus an adjustment `c(Size)`. This adjustment is for the unbuilt decision tree (for efficiency) beyond the max height. When `h(x)` is obtained for each tree, an anomaly score is produced by computing `s(x, sample_size)`. Sorting instances by the score `s` in descending order and getting top `m` will yield us `m` anomalies.

```py
def get_path_length(x, T, e):
  """The function returns the path length h(x) of an instance
  x in tree `T`.

  here e is the number of edges traversed from the root till the current
  subtree T.
  """
  if is_external_node(T):
    # when T is the root of an external node subtree
    # then we estimate path length and return.

    # here c is the function which estimates the average path length
    # for external node termination.
    return e + c(len(T))

  # T is the root of an internal node then we
  if x[T.split_attribute] < T[split_value]:
    # instance x may lie in left subtree
    return get_path_length(x, T.left, e + 1)
  else:
    # instance x may lie in right subtree
    return get_path_length(x, T.right, e + 1)
```

## Efficiency
Isolation forest algorithm
 - thrives on sub-sampled data
 - does not really need to build the tree from complete data
 - does not need to build tree taller than `max_height` which can be estimated very quickly
 - does not use any computationally expensive operation like distance or density calculation
 - has low memory footprint and linear time complexity with low constant for training
 - handles multi-dimensional data efficiently
 - could be used in an online system with low memory footprint (near real-time)

# Conclusion
I really hope this article helped you to understand Isolation Forest, an unsupervised anomaly detection algorithm. I stumbled upon this through an engineering [blog](https://lambda.grofers.com/anomaly-detection-using-isolation-forest-80b3a3d1a9d8) of [Grofers](https://grofers.com/). This algorithm was very interesting to me because of its novel approach and hence I dove deep into it. In 2018, Isolation Forest was extended by [Sahand Hariri, Matias Carrasco Kind, Robert J. Brunner](https://arxiv.org/pdf/1811.02141.pdf). I didn't read the extended Isolation Forest algorithm but have surely added it to my reading list and encourage you to do so.
