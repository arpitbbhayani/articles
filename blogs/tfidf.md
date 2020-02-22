TFIDF finds how important the word is for in a document for a corpus.

It does not only quantify the importance within doc but it also considers the corpus.

Score is Term Frequency in doc
Issue with stop words a, and, the (as they are most frequent)
Graph goes like this

How important word is in corpus
How many documents is the word present in
Again words like a and the has higer score.
Score = d/D

Do it in ascending
score = D/d
NUmerator is constant.
when w is frequent d -> D and score -> 1
when w is infrequent d -> 1 and score -> D
Now our score is bounded from 1 to D
Higher the score higher is the rarity and higher is the information that it provides

Doing it logarithmically
https://www.forbes.com/sites/naomirobbins/2012/01/19/when-should-i-use-logarithmic-scales-in-my-charts-and-graphs/#5b949e275e67
y\ =\ \log_{10}\left(x+1\right)

Log scales show relative values

Log scales show relative values instead of absolute ones. Log scales don’t care about the fact that 101 minus 100 equals the same as 2 minus 1. Instead, they are concerned with percentages: between 100 and 101 is a 1% increase, while between 1 and 2 is a 100% increase. So on a log scale, the distance between 100 and 101 is roughly 1% of the distance between 1 and 2

https://blog.datawrapper.de/weeklychart-logscale/

IDF = log(D/d)

We want the score to be closer 0 for frequent words and > 0 for infrequent words but would not grow exponentially. Growth is very slow. This should be tweaked as per corpus size and score range you aim for.
IDF shows if it's common or rare across all documents



tf-idf
A high weight in tf–idf is reached by a high term frequency (in the given document) and a low document frequency of the term in the whole collection of documents

---

Different IDF

Graphs: https://en.wikipedia.org/wiki/File:Plot_IDF_functions.png



The idea behind tf–idf also applies to entities other than terms. In 1998, the concept of idf was applied to citations.[10] The authors argued that "if a very uncommon citation is shared by two documents, this should be weighted more highly than a citation made by a large number of documents". In addition, tf–idf was applied to "visual words" with the purpose of conducting object matching in videos,[11] and entire sentences.[12] However, the concept of tf–idf did not prove to be more effective in all cases than a plain tf scheme (without idf). When tf–idf was applied to citations, researchers could find no improvement over a simple citation-count weight that had no idf component
