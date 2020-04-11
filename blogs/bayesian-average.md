The internet is filled with user reviews and ratings which are then used to rank products during listing - example Search results. Today we explore Bayesian Average as a strategy to calculate aggregated ranking of a product given user ratings.

Here we take an example of a Movie rating system through a Movie Lens dataset. The problem stattement could be summarized as

> Given the user ratings for each product, find the top k products

Movies, Restaurants, Hotels, Books, 

# Aggregation methods
Each product has several ratings but it will be extremely helpful that each product has an aggregated rating that indicates the true rating of the product - which helps user to make the decision. Example booking 

## Arithmetic Mean
The most common strategy of computing aggregated rating is Arithmetic Mean. In this for all movies we take sum all the ratings users submitted and divide it by the number of ratings that were submitted. This is the true arithmetic mean.

IMAGE: FORMULA

### Some issues with Arithmetic Mean

When cardinality is low the average rating could skew. It is not a true representaton of quality.

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

## Understanding the formula

## How this formula works?

## What it actually does?

# Applications of Bayesian Average

# Extra thought points

## Dealing with multi-dimensional data

## Tweaking the formula

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
