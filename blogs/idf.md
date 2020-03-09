TF-IDF is one of the most popular measure that quantifies document relevance for a term. It is extensively used in Information Retrieval (ex: Search Engines), Text Mining and for Text-heavy Machine Learning use cases. Today we explore the better half of TF-IDF and see the intuition behind it, its connection with Probability and its role in TF-IDF.

Inverse Document Frequency (IDF) is a measure of term rarity which means it quantifies how rare the term is in the corpus (document collection). The heuristic tells that rarer the term, the better it helps in discriminating, distinguishing and ranking documents and it contributes more information to the corpus than some frequent terms (like `a`, `the`, `and` etc).

The IDF was heuristically proposed in the paper "[A statistical interpretation of term specificity and its application in retrieval](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.115.8343&rep=rep1&type=pdf)" (Spärck Jones, 1972)  was originally called Term Specificity.

# The intuition behind IDF
A term that occurs in many documents should be given lesser weight than the one that occurs in a fewer documents. This measure is thus inversely proportional to the document frequency (number of documents in which the term is present) - and hence referred as Inverse Document Frequency.

IDF INVERSELY PROPORTIONAL TO DOCUMENTS IN WHICH WORD IS PRESENT

This means the words like `a`, `an`, `the`, etc that occurs in a lot of documents should be assigned a very small weight as compared to a term that occurs in a fewer document.

So any function that is inversely proportional to the document frequency could be used here. Some sample plots of function are shown below

SAMPLE INVERWSE FUNCTIONS

Depending on the nature of data we are playing with, the use case and how we want to decay the weight propertional to document frequency we could pick the function.

# The most common IDF
There are quite a few number of functions that fir the definition of IDF but the most common IDF function is

IDF FUNCTION

where

 N -> documents in the corpus,
 term ti occurs in ni of them

The original measure, suggested in the paper, was an integer approximation to this formula, and the logarithm was specifically to the base 2. However, as will be seen below,the base of the logarithm is not in general important.

# IDF's connection with probability
Probability that a document of the corpus contains the term ti is given by DTi/N where

PROBABILITY FORMULA

The fraction inside the logarithm in the common IDF function is inverse of the above probaility fraction and this helps us define IDF as a probability. And this heuristic beautifully binds with Probability and helps us redefine IDF in terms of the probability, andregard the observed IDF as an estimate of the true IDF. (Robertson, 1972)

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

REferences
 - https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396

Tools:
 - http://latex2png.com/
 