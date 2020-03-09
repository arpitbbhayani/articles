TF-IDF is one of the most popular measure that quantifies document relevance for a term. It is extensively used in Information Retrieval (ex: Search Engines), Text Mining and even for Text-heavy Machine Learning use cases like Classification and Clustering. Today we explore the better half of TF-IDF and see the intuition behind it, its connection with Probability and the role it plays in TF-IDF.

Inverse Document Frequency (IDF) is a measure of term rarity which means it quantifies how rare the term is in the corpus (document collection) - higher the IDF, rarer the term. The heuristic tells that a rare term helps in discriminating, distinguishing and ranking documents and contributes more information to the corpus than a frequent term (like `a`, `the` and `and`).

The IDF was heuristically proposed in the paper "[A statistical interpretation of term specificity and its application in retrieval](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.115.8343&rep=rep1&type=pdf)" (Spärck Jones, 1972) and was originally called Term Specificity.

# The intuition behind IDF
In order to quantify the term rarity we need to give higher weight to the term that occurs in fewer document and lesser weights to the frequent terms. Thus this measure (weight) `w` of the term is inversely proportional to the number of documents in which it is present (called Document Frequency) - and hence referred as Inverse Document Frequency.

![IDF Inversely proportional to Document Frequency](https://user-images.githubusercontent.com/4745789/76211536-85237d00-622c-11ea-82f5-c0b655634839.png)

Any function that adheres to the requirement of being inversely proportional to the document frequency would do the job; it may not be optimal for the use case but could bu used as an IDF. Some function plots that could fit as an IDF are shown below

![Decreasing functions](https://user-images.githubusercontent.com/4745789/76213296-63c49000-6230-11ea-9d24-94ce048732bc.png)

Since the words like `a`, `an` and `the` occurs in a lot of documents, they are assigned a very small weight. Picking the right function depends on the use case but since IDF is usually used for a text-heavy problem and since almost all text heavy systems follow [Zipf's law](https://en.wikipedia.org/wiki/Zipf%27s_law), a common IDF measure (elaborated below) is adapted widely and performs better in most use cases.

# The most common IDF
The most common IDF function is defined as

IDF FUNCTION

where

 - N -> documents in the corpus,
 - term ti occurs in ni of them

The plot of the IDF curve for above function vs document frequency shows the decay in weight as the document frequency increases. It is bounded by .... and reaches minimum at _-----.

# IDF's connection with probability
Probability that a document of the corpus contains the term ti is given by DTi/N where

PROBABILITY FORMULA

The fraction inside the logarithm in IDF function is oddly similar to the above probability estimation function. Observing closely we see that the fraction inside the logarithm is inverse of the probability defined above and hence we could redefine IDF using this probability (Robertson, 1972) as 

IDF AS PROBABILITY

# IDF of multiple terms
Computing IDf for a single term is fine but what happens when we have multiple terms? This is a very common usecase in Information Retrieval where we need to rank documents for a given search query containing multiple terms.

For finding IDF of multiple terms in conjugation we assume that the occurances of terms are statistically independent and hence 

PROBABILITY OF TeRM IN CONJUGATION IS MULTIPLICATION OF BOTH

We could derive the IDF of two terms in conjugation as follows

DERIVATION

Thus we see that by using IDF the document scoring function scores a document by the sum of the weights of the query terms it contains. Although this could be made much more complex by not assuming statistical independence.

# Other measures of IDF
Apart from common IDF function as seen above there are other IDF measures that are widely used, they are:

IDF MEASUREES AND PLOT

# Role of IDF in TF-IDF
TF-IDF suggests how important a word is to a document in a collection or corpus and is primarily the product of Term Frequency and Inverse Document Frequency. It helps search engines identify what it is that makes a given document special. For the document to have a high TF-IDF score it needs to have high term frequency and a low document frequency of the term. This IDF primarily down scales the frequent occuring (high term frequency) of common words and boosts high term frequency of infrequent words.

the weights hence tend to filter out common terms. 
For a sample document in Harry Potter Corpus see what happens.

EXAMPLE

# References
 - [TF-IDF - Wikipedia](https://en.wikipedia.org/wiki/Tf%E2%80%93idf)
 - [Understanding Inverse Document Frequency:On theoretical arguments for IDF](https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396)
 - [Inverse Document Frequency and the Importance of Uniqueness](https://moz.com/blog/inverse-document-frequency-and-the-importance-of-uniqueness)
 - http://latex2png.com/
