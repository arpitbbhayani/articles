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
Assume there areNdocuments in the collection, and that termtioccurs inniof them. (Whatmight constitute a ‘term’ is not of concern to us here, but we may assume that terms arewords, or possibly phrases or word stems. ‘Occurs in’ is taken as shorthand for ‘is an indexterm for’, again ignoring all the difficulties or subtleties of either automatic indexing fromnatural language text, or human assignment of index terms.) Then the measure proposed bySparck Jones, as a weight to be applied to termti, is essentiallyidf(ti) = logNni(1)Actually this is not quite accurate – the original measure was an integer approximation tothis formula, and the logarithm was specifically to the base 2. However, as will be seen below,the base of the logarithm is not in general important.

any function is bounded and decreases with increase in x could be used instead of IDF

-Df
-Df/N
N/Df

# IDF's connection with probability

The fraction inside the logarithm in equation 1 looks like it might represent a probability(actually inverted).
hus we can consider the probability that a random documentdwould contain the term (Robertson, 1972). This probability has an obvious estimate, namely theinverse of the fraction in the IDF equatio

In the light of this relation, we can reasonably redefine IDF in terms of the probability, andregard the observed IDF as an estimate of the true IDF

# Combined IDF

One important feature of term weighting schemes is that it is frequently assumed thatdocument scoring functions will be essentially additive. Thus if for example we have threequery termst1,t2,t3, and we give them simple weightsw1,w2,w3, then a common simplescoring function would score a document by the sum of the weights of the query terms itcontains. So a document containing all three terms would scorew1+w2+w3, while onecontaining only termst1andt3would scorew1+w3.  Clearly scoring functions can beconsiderably more complex than this, and we will encounter some below, but most are basedon the addition of separate term components as a basic assumption

We can combine the probabilistic interpretation of IDF and the idea of an addition-basedscoring function very simply and elegantly: if we assume that the occurrences of differentterms in documents are statistically independent, then addition is the correct thing to dowith the logs. That is,idf(t1∧t2)  =−logP(t1∧t2)=−log(P(t1)P(t2))=−(logP(t1) + logP(t2))=idf(t1) +idf(t2)

Heret1∧t2represents the ‘term’ which is the Booleanandoft1andt2. The same argumentapplies to any number of terms. Thus taking logs and then adding the weights is exactly theright thing to do. We may also note that if the reason for taking logs is to be able to addthem, then the base of the logarithm does not matter.Of course we do not really assume that the terms are statistically independent. Neverthe-less, that simplifying assumption at least suggests strongly that we should use the log ratherthan (say) a linear function of the fractionN/ni, which would be equally compatible with theoriginal intuition.

---
# Role of IDF in TF-IDF
IDF downscales unimportant word

---
Other measures of IDF


---


REferences
 - https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396

Tools:
 - http://latex2png.com/
 