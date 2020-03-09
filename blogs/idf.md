[TF-IDF](https://en.wikipedia.org/wiki/Tf%E2%80%93idf) is one of the most popular measures that quantifies document relevance for a given term. It is extensively used in [Information Retrieval](https://en.wikipedia.org/wiki/Information_retrieval) (ex: Search Engines), Text Mining and even for text-heavy Machine Learning use cases like Document Classification and Clustering. Today we explore the better half of TF-IDF and see its connection with Probability, role it plays in TF-IDF and even the intuition behind it.

Inverse Document Frequency (IDF) is a measure of term rarity which means it quantifies how rare the term, in the corpus, really is (document collection); higher the IDF, rarer the term. A rare term helps in discriminating, distinguishing and ranking documents and it contributes more information to the corpus than what a more frequent term (like `a`, `and` and `the`) does.

The IDF was heuristically proposed in the paper "[A statistical interpretation of term specificity and its application in retrieval](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.115.8343&rep=rep1&type=pdf)" (Spärck Jones, 1972) and was originally called Term Specificity.

# The intuition behind IDF
In order to quantify the term rarity, the heuristic says we need to give higher weight to the term that occurs in fewer documents and lesser weights to the frequent ones. Thus this measure (weight) `w` of the term is __inversely proportional__ to the number of documents in which it is present (called Document Frequency) - and hence the measure is called Inverse Document Frequency.

![IDF Inversely proportional to Document Frequency](https://user-images.githubusercontent.com/4745789/76211536-85237d00-622c-11ea-82f5-c0b655634839.png)

Any function that adheres to the requirement of being inversely proportional to the document frequency i.e. a decreasing function, would do the job; it may not yield optimality but could be used as an IDF for some use cases. Some decreasing functions that could be used as an IDF for some use cases are shown below

![Decreasing functions](https://user-images.githubusercontent.com/4745789/76213296-63c49000-6230-11ea-9d24-94ce048732bc.png)

The more frequent words, like `a`, `and` and `the` will lie on the far right of the plot and will have smaller value of IDF. Since IDF is usually used for a text-heavy problem statement and almost all text-heavy systems follow [Zipf's law](https://en.wikipedia.org/wiki/Zipf%27s_law), a widely adapted IDF measure (elaborated below) performs better in most use cases.

# The most common IDF
The most common IDF function is defined as

![common idf function](https://user-images.githubusercontent.com/4745789/76215222-4bef0b00-6234-11ea-8d03-3ad9663837da.png)

where

 - N is the number of documents in the corpus
 - term t occurs in df_t documents

The plot of the IDF curve for the above function vs document frequency shows the decay in weight as the document frequency increases. It is bounded by .... and reaches a minimum at _-----.

![IDF Graph](https://user-images.githubusercontent.com/4745789/76215908-ae94d680-6235-11ea-8e50-498aae029ea2.png)

# IDF's connection with probability
The probability that a document of the corpus contains the term ti is given by DTi/N where

![Probability](https://user-images.githubusercontent.com/4745789/76229411-29ff8380-6248-11ea-9518-6cbc4c6947da.png)

The fraction inside the logarithm in the IDF function is oddly similar to the above probability estimation function. Observing closely we see that the fraction inside the logarithm is inverse of the probability defined above and hence we could redefine IDF using this probability (Robertson, 1972) as 

![IDF as probability](https://user-images.githubusercontent.com/4745789/76229704-a09c8100-6248-11ea-9960-0cfd5f45dcce.png)

# IDF of multiple terms
Computing IDF for a single term is fine but what happens when we have multiple terms? This is a very common use-case in Information Retrieval where we need to rank documents for a given search query containing multiple terms.

For finding IDF of multiple terms in conjugation we assume that the occurrences of terms are statistically independent and hence 

![Probability of conjugation](https://user-images.githubusercontent.com/4745789/76231077-b317ba00-624a-11ea-86f4-4b517fb5799c.png)

We could derive the IDF of two terms in conjugation as follows

![IDF derivation](https://user-images.githubusercontent.com/4745789/76232475-c2980280-624c-11ea-8a3a-37d17704a221.png)

Thus we see that by using IDF the document scoring function scores a document by the sum of the weights of the query terms it contains. Although this could be made much more complex by not assuming statistical independence.

# Other measures of IDF
Apart from common IDF function as seen above there are other IDF measures that are widely used, they are:

![Other IDF Measures](https://user-images.githubusercontent.com/4745789/76232678-0db21580-624d-11ea-864c-1094559e0790.png)

![Plot IDF Functions](https://user-images.githubusercontent.com/4745789/76232756-2de1d480-624d-11ea-81cb-8d29109bd594.png)

# Role of IDF in TF-IDF
TF-IDF suggests how important a word is to a document in a collection or corpus and is primarily the product of Term Frequency and Inverse Document Frequency. It helps search engines identify what it is that makes a given document special. For the document to have a high TF-IDF score it needs to have high term frequency and a low document frequency of the term. This IDF primarily downscales the frequent occurring (high term frequency) of common words and boosts high term frequency of infrequent words.

the weights hence tend to filter out common terms. 
For a sample document in Harry Potter Corpus see what happens.

EXAMPLE

# References
 - [TF-IDF - Wikipedia](https://en.wikipedia.org/wiki/Tf%E2%80%93idf)
 - [Understanding Inverse Document Frequency: On theoretical arguments for IDF](https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396)
 - [Inverse Document Frequency and the Importance of Uniqueness](https://moz.com/blog/inverse-document-frequency-and-the-importance-of-uniqueness)
 - http://latex2png.com/

Images used in other measures of IDF are taken from [Wikipedia page of TF-IDF](https://en.wikipedia.org/wiki/Tf%E2%80%93idf) and the derivation equation of IDF in conjugation is taken from the paper [Understanding Inverse Document Frequency: On theoretical arguments for IDF](https://pdfs.semanticscholar.org/8397/ab573dd6c97a39ff4feb9c2d9b3c1e16c705.pdf?_ga=2.255772288.944438221.1583673396-1263237981.1583673396).
