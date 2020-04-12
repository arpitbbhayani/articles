Almost every single website, app or platform on the internet has some sort of rating system in place. Whenever you purchase a product or use a service, you are asked to rate it on a scale, say 1 to 5. The platform then uses this data to generate a score and build a ranking system around it. The score is the measure of quality for each product or service. By surfacing quality content on top the platform tries up their selling and surface the most quality content to their users.

Coming up with the aggregated score is not an easy thing - we need to crunching millions of ratings and then see that the score is, in fact, the true measure of quality. If it isn't then it would directly affect the business. Today we discuss how we should define this score in a rating based system; spoiler alert! the measure is called [Bayesian Average](https://en.wikipedia.org/wiki/Bayesian_average).

To keep things simple we define the problem statement as

> Given the ratings that users give to a movie, on a scale of 1 to 5, we generate a score that is a measure of how good a movie is and it helps us get the top 10 movies of all time.

# Generating the score
The score we generate for each will be computed by using the individual ratings; and will also be a measure of its quality, which means higher the score, superior is the product. Hence we say that the score is the function of all the `m` ratings that the product got.

![score function](https://user-images.githubusercontent.com/4745789/79067003-cf8b9400-7cd9-11ea-9b16-c1875933725a.png)

## Arithmetic Mean
The simplest and the most common strategy to compute this aggregated score is by taking an arithmetic mean (average). Hence for each product we sum all the ratings that it got and divide it by the number of ratings it got, giving us an average value.

![arithmetic mean](https://user-images.githubusercontent.com/4745789/79049349-b387e400-7c40-11ea-9adf-b40aa377778f.png)

### Issues with arithmetic mean
The arithmetic mean falls apart pretty quickly. Let's say there is a product with just one rating of 5 on 5, the product would soar high on the leaderboard ranking. But does it deserve that place? probably not. Thus arithmetic mean suffers from the cardinality issue which means the items with low cardinality (low number of ratings) will fluctuate between highs and lows of ranking.

With the movie dataset we are playing with here is the top 10 movies ranked using Arithmetic Mean.

![top 10 movies arithmetic mean](https://user-images.githubusercontent.com/4745789/79049814-58a3bc00-7c43-11ea-980e-a12ae10379f7.png)

Through this measure, all the movies that are in top 10 have average score of 5 (out of 5) and have just 1 rating. But, in reality, are these really the top 10 movies of all time? Looks like we can do a lot better than the arithmetic mean.

## Cumulative Rating
To remedy the issue with low cardinality in Arithmetic Mean, we could come up with an approach of using Cumulative Rating as the scoring function which means instead of taking the average we only consider the sum of all the ratings as the final score.

![cumulative rating as scoring function](https://user-images.githubusercontent.com/4745789/79050470-e1245b80-7c47-11ea-824b-ecd5cbb40912.png)

Cumulative Rating does a pretty decent job, it makes popular items with a large number of ratings bubble up to the top of the leaderboard. We can see this in action when applied to our Movie dataset.

![top 10 movies through cunulative rating](https://user-images.githubusercontent.com/4745789/79050520-2d6f9b80-7c48-11ea-8e48-1c12fbbc0a88.png)

The top 10 now features Shawshank Redemption, Forrest Gump, Pulp Fiction, etc. which are in fact the top movies of all times. But is Cumulative Rating fool-proof?

### Issues with cumulative rating
Cumulative Rating favors high cardinality. Let's say there is an extremely popular item `A` that got 10000 ratings of 1 on 5, while there is another item `B` that got 1000 rating of 5 on 5. When we apply cumulative rating we find that the score of `A` is 10000 while that of `B` will be 5000, but we could see that item `B` is far superior to `A`.

Another issue with Cumulative Rating is the fact that it generates and unbounded score. Ideally, any ranking system expects a normalized bounded score so that it becomes predictable and easy to determine the position and measure quality.

Thus we see although Cumulative Rating, in a usual scenario, will do a good job, the system is not fool-proof and that's where the Bayesian Average comes to the rescue.

# The Bayesian Average
Bayesian Average computes the mean of a population by not only consider the data residing in the population but also considering outside information, like a pre-existing belief - a derived property from the dataset ex: prior mean.

## The intuition
The major problem with Arithmetic Mean as the scoring function was how unreliable it was when we had a low number of data points (cardinality) to compute the score. Bayesian Average plays a part here by introducing pre-belief like Prior Mean, into the scheme of things.

We would want our scoring system to be adhering to the following rules

 - an item has a fewer than average number of ratings - the score should be around the system's arithmetic mean
 - an item has a substantial number of ratings - the score should be the item's arithmetic mean

By doing the above we ensure that we do not either prematurely promote or demote an item in the leaderboard. The item is given a fair number of chances until it receives a substantial number of ratings. This way we use the prior-belief making the scoring function more robust and fair to all items.

## The formula
Given the intuition and scoring rules, we could come up with the following formula

![bayesian average formula for rating system](https://user-images.githubusercontent.com/4745789/79066315-ab798400-7cd4-11ea-804b-e5e8479824b2.png)

In the above formula `w` indicates the weight that needs to be given the item's Arithmetic Mean `A` while `S` represents the System's Arithmetic Mean. If `A` and `S` are bounded then the final score `s` will also be bounded in the same range, thus solving the problem with Cumulative Rating.

Suppose we denote the number of ratings that an item `i` received by `m` and the average number of ratings that an item in the system receives by `M`, we define the requirements of `w` as follows

 - `w` is bounded in range `[0, 1]`
 - `w` should be monotonically increasing
 - `w` should be close to `0` when `m` is close to `0`
 - `w` should reach `0.5` when number `m` reaches `M`
 - `w` tries to get closer to `1` as `m` increases

Considering the above requirements a `w` could be defined as

![weight function for bayesian average](https://user-images.githubusercontent.com/4745789/79066802-4162de00-7cd8-11ea-8068-467ce3305810.png)

When we combine all of the above we get the final scoring function as

![scoring function for bayesian average rating system](https://user-images.githubusercontent.com/4745789/79066769-111b3f80-7cd8-11ea-979e-6437334ccbba.png)

Once we apply the function to our Move Dataset we get the following movies as the top 10

![top 10 movies by Basysian Average](https://user-images.githubusercontent.com/4745789/79066961-686ddf80-7cd9-11ea-87d7-7e7e582ab9ac.png)

Changes in position

![Kingsman position with ratings](https://user-images.githubusercontent.com/4745789/79068414-53e31480-7ce4-11ea-884a-90e7aee326d8.png)

![Logan rankings](https://user-images.githubusercontent.com/4745789/79068443-7f65ff00-7ce4-11ea-9623-6f03451235de.png)

![Scorpion King](https://user-images.githubusercontent.com/4745789/79068524-35c9e400-7ce5-11ea-8726-d1836a6b9c23.png)

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

[![Subscribe to Arpit's newsletter](https://user-images.githubusercontent.com/4745789/79068776-07e59f00-7ce7-11ea-8eff-3918556a3682.png)](https://arpit.substack.com)
