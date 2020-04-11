Almost every single website, app or platform on the internet has some sort rating system in place. Whenever you purchase a product or use a service, you are asked to rate it on a scale, say 1 to 5. The platform then uses this data to generate a score and build a ranking system around it. The score is the measure of quality for each product or service. By surfacing quality content on top the platform tries up their selling and serve the most quality content to their users.

Coming up with the aggregated score is not a easy thing - we need to curnching millions of ratings and then see that the score is infact the true measure of quality. If it isn't then it would directly affect the business. Today we discuss how we should define this score in a rating based system; spoiler alert! the measure is called [Bayesian Average](https://en.wikipedia.org/wiki/Bayesian_average).

To keep things simple we define the problem statement as

> Given the ratings that users gives to a movie, on a scale of 1 to 5, we generate a score that is a measure of how good a movie is and it helps us get the top 10 movies of all time.

# Generating the score
The score we generate for each will be computed by using the individual ratings; and willalso be a measure of its quality, which means higher the score, superior is the product. Hence we say that the score is the function of all the `m` ratings that the product got.

![score function](https://user-images.githubusercontent.com/4745789/79049127-31e38680-7c3f-11ea-9032-baa0d2152cc2.png)

## Arithmetic Mean
The simplest and the most common strategy to compute this arrgregated score is by taking an arithmetic mean (average). Hence for each product we sum all the ratings that it got and divide it by the number of ratings it got, giving us an average value.

![arithmetic mean](https://user-images.githubusercontent.com/4745789/79049349-b387e400-7c40-11ea-9adf-b40aa377778f.png)

### Issues with arithmetic mean
Arithmetic mean falls apart pretty quickly. Let's say there is a product with just one rating of 5 on 5, the product would soar high on the leaderboard ranking. But does it deserve that place? probably not. Thus arithmetic mean suffes from the cardinality issue which means the items with low cardinality (low number of ratings) will fluctuate between highs and lows of ranking.

With the movie dataset we are playing with here is the top 10 movies ranking using Arithmetic Mean.

![top 10 movies arithmetic mean](https://user-images.githubusercontent.com/4745789/79049814-58a3bc00-7c43-11ea-980e-a12ae10379f7.png)

All the movies that are in top 10 have average score of 5 on 5 and have 1 or 2 ratings in totality. But are these really the top 10 movies? Nope. We can do a lot better than arithmetic mean.

## Cumulative Rating
We could assign the score as a summation of all the ratings received.

IMAGE: function

This approach does a pretty good job in getting the top k. as shown in the table below.

IMAGE: example

### Issues
The ranking looks good but it suffers from the problem. 10k ratings of 1 start vs 500 ratings of 5 star.

# The Bayesian Average
Bayesian average tries to address all of the above problem.

## The intuition
Unless we are sure that the rating will give the true rating of a movie we need to use system average. Once given a number of opportunities we would consider the rating it received as true rating.

Bayesian average of items is given by

IMAGE: FORMULA

## Understanding the formula

Given weight to prior.

## How this formula works?

When m = 0, unless it reaches the avg number of rating we cannot say for sure.

# Applications of Bayesian Average
Movies, Restaurants, Hotels, Books, 

# Extra thought points

## Dealing with multi-dimensional data

## Tweaking the formula

# References

---

_Other articles you might like:_
 - [Sliding window based Rate Limiter](https://arpitbhayani.me/blogs/sliding-window-ratelimiter)
 - [Understanding Inverse Document Frequency](https://arpitbhayani.me/blogs/idf)
 - [Eight rituals to be a better programmer](https://arpitbhayani.me/blogs/better-programmer)
 - [Pseudorandom numbers using Cellular Automata - Rule 30](https://arpitbhayani.me/blogs/rule-30)
 - [Overload Functions in Python](https://arpitbhayani.me/blogs/function-overloading)
 - [Isolation Forest algorithm for anomaly detection](https://arpitbhayani.me/blogs/isolation-forest)

_This article was originally published on my [blog - Sliding window based Rate Limiter](https://arpitbhayani.me/blogs/sliding-window-ratelimiter)._

_If you liked what you read, subscribe to my newsletter and get the post delivered directly to your inbox and give me a shout-out [@arpit_bhayani](https://twitter.com/arpit_bhayani)._

[![Subscribe to Arpit's newsletter](https://user-images.githubusercontent.com/4745789/74005152-fc4fc200-499d-11ea-9df7-9f6733a06aa8.png)](https://arpit.substack.com)
