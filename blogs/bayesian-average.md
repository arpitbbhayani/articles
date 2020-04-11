Almost every single website, app or platform on the internet has some sort rating system in place. Whenever you purchase a product or use a service, you are asked to rate it on a scale, say 1 to 5. The platform then uses this data to generate a score and build a ranking system around it. The score is the measure of quality for each product or service. By surfacing quality content on top the platform tries up their selling and serve the most quality content to their users.

Building a ranking is not as easy as it sounds. Curnching millions of ratings and coming with one consolidate and aggregated number is a touch problem on its own. Today we discuss several approaches for coming up with this aggregated rating for a product and see why a approach called Bayesian Average does wonderfully well.

To set things up for this roller coaster ride we first define the problem statement, that we will then dissect to understand ranking strategies.

> Given the user ratings, on a scale of 1 to 5, for movies, we find top 10 movies of all time.

# Aggregation methods
In order to find top 10 movies, we need a way to assign a `score` to each movie that defines how good it is. This score has to be computed from all the ratings that the movie has received till date. Thus the final score of the move will be

IMAGE: score is a function of all ratings it has received

Deciding this function `fn` is what we do today.

## Arithmetic Mean
The most common strategy of computing aggregated rating is Arithmetic Mean. In this for all movies we take sum all the ratings users submitted and divide it by the number of ratings that were submitted. This is the true arithmetic mean.

IMAGE: FORMULA

This is what we usually do when someone asks to have an "average" rating.

### Some issues with Arithmetic Mean
If you set score of an item to be equal to arithmetic mean of all its rating, then what about an item that gets just one rating which is a 5 on 5. That item will have be rank 1. This seems wrong.

IMAGE: Ranking movies with AA

The core issue here is the cardinality. While taking arithmetic mean the low cardinality items dominate the top or the bottom positions in the leaderboard. Thus we establish the fact that Arithmetic mean is not the score we would want to go ahead with.

## Arithmetic Mean with Cardinality
If cardinality is the issue we could try to patch things by considering not only the score but also the cardinality. This way we assign a score tuple `(average_score, ratings_count)` as the final score and we sort items in descending order. Thus in case of a tie of score the conflict will be resolved using number of ratings.

IMAGE: score

### Issues
This solution tries to address the issue but fails to do a good job. Movie example:

IMAGE: Movie example:

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
