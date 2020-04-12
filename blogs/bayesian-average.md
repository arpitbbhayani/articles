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

Through this measure, all the movies that are in top 10 have average score of 5 (out of 5) and have just 1 rating. But, in reality, are these really the top 10 movies of all time? Looks like we can do a lot better than arithmetic mean.

## Cumulative Rating
To remedy the issue with low cardinality in Arithmetic Mean, we could come up with an approach of using cumulative rating as the scoring function which means instead of taking the average we only consider the sum of all the ratings as the final score.

![cumulative rating as scoring function](https://user-images.githubusercontent.com/4745789/79050470-e1245b80-7c47-11ea-824b-ecd5cbb40912.png)

Cumulative rating does a pretty decent job, it makes popular items with large number of ratings bubble up to the top of the leaderboard. We can see this in action when applied to our Movie dataset.

![top 10 movies through cunulative rating](https://user-images.githubusercontent.com/4745789/79050520-2d6f9b80-7c48-11ea-8e48-1c12fbbc0a88.png)

The top 10 now features Shawshank Redemption, Forrest Gump, Pulp Fiction, etc. which are in fact the top movies of all times. But is Cumulative Rating fool-proof?

### Issues with cumulative rating
Cumulative rating favours high cardinality. Let's say there is an extremely popular item `A` that got 10k rating of 1 on 5, while there is another item `B` that got 1k rating of 5 on 5. When we apply cumulative rating we find that the score of `A` is 10000 while that of `B` will be 5000, but we could see that item `B` is far superior than `A`.

Another issue with Cumulative rating is the fact that it generates and unbounded score. Ideally any ranking system expects a normalized bounded score, so that it becomes predicatable and easy to determine the position and measure quality.

Thus we see although cumulative rating, in a usual scenario, will do a good job, the system is not fool-proof and that's where the Bayesian Average comes to the rescue.

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
