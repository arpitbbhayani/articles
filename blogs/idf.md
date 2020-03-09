TF-IDF is one of the most popular measure that quantifies document relevance for a term. It is extensively used in Information Retrieval (Search Engines), Text Mining and for Text-heavy Machine Learning use cases. Today we take a deeper look into the better half of TF-IDF - IDF and dissect it ...

Inverse Document Frequency (IDF) is a measure of _term rarity_ which means it suggests how rare the term is in the corpus. By intuition, this term rarity is proportional to the information the word contributes to the corpus. We could say, if a word is present in nearly all the documents (not rare) it could not provide sufficient information to distinguish, discriminate or rank documents.

The IDF was heuristically proposed in the paper "[A statistical interpretation of term specificity and its application in retrieval](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.115.8343&rep=rep1&type=pdf)" (Spärck Jones, 1972)  was originally called Term Specificity.

# The intuition behind IDF
A term that occurs in many documents should be given lesser weight than the one that occurs in a fewer documents. This heuristic measure is thus inversely proportional to the document frequency (number of documents in which the term `t` is present) - and hence it is referred as Inverse Document Frequency.

IDF INVERSELY PROPORTIONAL TO DOCUMENTS IN WHICH WORD IS PRESENT

This means the words like `a`, `an`, `the`, etc that occues in a lot of documents should be givren a very small weight as compared to a term that occus in a fewer document. This rare term helps us discrimirate and distinguish relevant document.

Any function that meets this criteria could be used in this regard few sample functions are

SAMPLE INVERWSE FUNCTIONS

# The most common IDF
The most common IDF function is

IDF FUNCTION

where

 N -> documents in the corpus,
 term ti occurs in ni of them

the original measure was an integer approximation tothis formula, and the logarithm was specifically to the base 2. However, as will be seen below,the base of the logarithm is not in general important.

# IDF's connection with probability
Probability that a document contains a term ti is given by DTi/N.

This is inverse of The fraction inside the logarithm in equation 1 of IDF.

Another way to put IDF becomes: Thus we can consider the probability that a random documentd would contain the term (Robertson, 1972). This probability has an obvious estimate, namely theinverse of the fraction in the IDF equatio.s In the light of this relation, we can reasonably redefine IDF in terms of the probability, andregard the observed IDF as an estimate of the true IDF

# Additivity of IDF
What would be the IDF of t1 and t2?
LEts derive.


document scoring functions will be essentially additive. simplescoring function would score a document by the sum of the weights of the query terms itcontains So a document containing all three terms would scorew1+w2+w3, while onecontaining only termst1andt3would scorew1+w3.

We can combine the probabilistic interpretation of IDF and the idea of an addition-basedscoring function very simply and elegantly: if we assume that the occurrences of differentterms in documents are statistically independent, then addition is the correct thing to dowith the logs. That is,idf(t1∧t2)  =−logP(t1∧t2)=−log(P(t1)P(t2))=−(logP(t1) + logP(t2))=idf(t1) +idf(t2)

Clearly scoring functions can beconsiderably more complex than this, and we will encounter some below, but most are basedon the addition of separate term components as a basic assumption

if the reason for taking logs is to be able to addthem, then the base of the logarithm does not matter.
if the reason for taking logs is to be able to addthem, then the base of the logarithm does not matter.

# Other measures of IDF

# Role of IDF in TF-IDF
IDF downscales unimportant word

---

REferences
 - https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396

Tools:
 - http://latex2png.com/
 