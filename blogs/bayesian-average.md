Almost every single website/app/platform on the internet has some sort rating system in place. Whenever you purchase a product or use a service you are asked to rate it on a scale, say 1 to 5. The platform then uses this data to build a ranking for each product/service so that they could surface the best products first and thus driving large number of sales.

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

### Some issues with Arithmetic Mean

When cardinality is low the average rating could skew. It is not a true representaton of quality.
This means that we if 1 restaurant had 1 vote and with rating of 10, it would not be the number one. (If we just got the average, it would be at the top! – and that would be wrong)

## Arithmetic Mean with Cardinality

To fix arithmetic mean, we could path things with the cardinatity where we first sort on the basis of average rating and then on cardinaility. This wouldn't ame the solution any better

### Issues
Even this suffers from the issue with skew.

## Cumulative Rating

Another approach we could be to use cumulative score. Now show the end rating to the user but have an score. Summation of all the ratings we ever received.

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
