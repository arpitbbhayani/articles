TF-IDF is one of the most popular measure that quantifies document relevance for a term. It is often used in Search Engines (Information Retrieval), Text Mining and Text Heavy Machine Learning use cases. Today we take a deeper look into the IDF part of TF-IDF and dissect it in greater detail.

Inverse Document Frequency is measure of term rarity and was first proposed in the paper “Astatistical interpretation of term specificity and its application in retrieval” (Sparck Jones,1972) and was originallyy called Term Specificity. IDF has proved to be a giant leap in the field of information retrieval but It was more of a heuristic measure of rarity and it does not have a tehoretical explaination.

# The intuition behind IDF
The intuition was that a query term which occurs in many documents is not a good discriminator,and should be given less weight than one which occurs in few documents, and the measure was an heuristic implementation of this intuition.


based on counting the number of documents inthe collection being searched which contain (or are indexed by) the term in question



Coupled with TF (the frequency of the term in the document itself,in this case, the more the better), it found its way into almost every term weighting scheme


---

The basic IDF

Assume there areNdocuments in the collection, and that termtioccurs inniof them. (Whatmight constitute a ‘term’ is not of concern to us here, but we may assume that terms arewords, or possibly phrases or word stems. ‘Occurs in’ is taken as shorthand for ‘is an indexterm for’, again ignoring all the difficulties or subtleties of either automatic indexing fromnatural language text, or human assignment of index terms.) Then the measure proposed bySparck Jones, as a weight to be applied to termti, is essentiallyidf(ti) = logNni(1)Actually this is not quite accurate – the original measure was an integer approximation tothis formula, and the logarithm was specifically to the base 2. However, as will be seen below,the base of the logarithm is not in general important.

---

Dissecting IDF


---

IDF's connection with probability

The fraction inside the logarithm in equation 1 looks like it might represent a probability(actually inverted).
hus we can consider the probability that a random documentdwould contain the term (Robertson, 1972). This probability has an obvious estimate, namely theinverse of the fraction in the IDF equatio

In the light of this relation, we can reasonably redefine IDF in terms of the probability, andregard the observed IDF as an estimate of the true IDF

---

One important feature of term weighting schemes is that it is frequently assumed thatdocument scoring functions will be essentially additive. Thus if for example we have threequery termst1,t2,t3, and we give them simple weightsw1,w2,w3, then a common simplescoring function would score a document by the sum of the weights of the query terms itcontains. So a document containing all three terms would scorew1+w2+w3, while onecontaining only termst1andt3would scorew1+w3.  Clearly scoring functions can beconsiderably more complex than this, and we will encounter some below, but most are basedon the addition of separate term components as a basic assumption

We can combine the probabilistic interpretation of IDF and the idea of an addition-basedscoring function very simply and elegantly: if we assume that the occurrences of differentterms in documents are statistically independent, then addition is the correct thing to dowith the logs. That is,idf(t1∧t2)  =−logP(t1∧t2)=−log(P(t1)P(t2))=−(logP(t1) + logP(t2))=idf(t1) +idf(t2)

Heret1∧t2represents the ‘term’ which is the Booleanandoft1andt2. The same argumentapplies to any number of terms. Thus taking logs and then adding the weights is exactly theright thing to do. We may also note that if the reason for taking logs is to be able to addthem, then the base of the logarithm does not matter.Of course we do not really assume that the terms are statistically independent. Neverthe-less, that simplifying assumption at least suggests strongly that we should use the log ratherthan (say) a linear function of the fractionN/ni, which would be equally compatible with theoriginal intuition.

---

Role in TF-IDF
IDF downscales unimportant word

---

Other measures of IDF



---


REferences
 - https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396

Tools:
 - http://latex2png.com/
 