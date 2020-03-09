TF-IDF is one of the most popular measure that quantifies document relevance for a term. It is extensively used in Information Retrieval (ex: Search Engines), Text Mining and even for Text-heavy Machine Learning use cases like Classification and Clustering. Today we explore the better half of TF-IDF and see the intuition behind it, its connection with Probability and the role it plays in TF-IDF.

Inverse Document Frequency (IDF) is a measure of term rarity which means it quantifies how rare the term is in the corpus (document collection) - higher the IDF, rarer the term. The heuristic tells that a rare term helps in discriminating, distinguishing and ranking documents and contributes more information to the corpus than a frequent term (like `a`, `the` and `and`).

The IDF was heuristically proposed in the paper "[A statistical interpretation of term specificity and its application in retrieval](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.115.8343&rep=rep1&type=pdf)" (Spärck Jones, 1972) and was originally called Term Specificity.

# The intuition behind IDF
In order to quantify the term rarity we need to give higher weight to the term that occurs in fewer document and lesser weights to the frequent terms. Thus this measure (weight) `w` of the term is inversely proportional to the number of documents in which it is present (called Document Frequency) - and hence referred as Inverse Document Frequency.

IDF INVERSELY PROPORTIONAL TO DOCUMENTS IN WHICH WORD IS PRESENT

Any function that adheres to the requirement of being inversely proportional to the document frequency would do the job; it may not be optimal for the use case but could bu used as an IDF. Some function plots that could fit as an IDF are shown below

SAMPLE INVERWSE FUNCTIONS

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
What would be the IDF of t1 and t2?
LEts derive.

Assume
 - occurrences of different terms in documents are statistically independent

We can combine the probabilistic interpretation of IDF and the idea of an addition-basedscoring function very simply and elegantly: if we assume that the , then addition is the correct thing to dowith the logs. That is,idf(t1∧t2)  =−logP(t1∧t2)=−log(P(t1)P(t2))=−(logP(t1) + logP(t2))=idf(t1) +idf(t2)

document scoring functions will be essentially additive. simplescoring function would score a document by the sum of the weights of the query terms itcontains So a document containing all three terms would scorew1+w2+w3, while onecontaining only termst1andt3would scorew1+w3.


Clearly scoring functions can beconsiderably more complex than this, and we will encounter some below, but most are basedon the addition of separate term components as a basic assumption

if the reason for taking logs is to be able to addthem, then the base of the logarithm does not matter.

# Other measures of IDF
Other popular measures of IDFs are:

 - A
 - B
 - C

When plotted looks like this.

# Role of IDF in TF-IDF
TF-IDF suggests important a word is to a document in a collection or corpus.
The tf–idf value increases proportionally to the number of times a word appears in the document and is offset by the number of documents in the corpus that contain the word, which helps to adjust for the fact that some words appear more frequently in general

IDF downscales unimportant word

A high weight in tf–idf is reached by a high term frequency (in the given document) and a low document frequency of the term in the whole collection of documents; the weights hence tend to filter out common terms. 

---

It helps search engines identify what it is that makes a given document special.


REferences
 - https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396

Tools:
 - http://latex2png.com/
 