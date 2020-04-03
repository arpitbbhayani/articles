A rate limiter restricts intended or unintended execssive usage of a system by regulating the number of requests made to/from it by discarding the surplus ones. In this article we dive deep into a intuitive and heuristic approach for rate limiting using sliding window; other approaches include "", "" and "".

Rate limiting is usually applied per access token or per user or per region/ip. For a generic rate limiting system this is abstracted by a `key` on which the limit will be configured; the key could hold any of the aforementioned value. The limit is defined as the number of requests `nr` allowed within a time window `tw` (defined in seconds).

# The algorithm
The algorithm is pretty intuitive, and could be summarized as follow

> If the number of requests served on key `key` in last `tw` seconds is more than `nr` then block or else the the request go through and update the counter.

Although the above gist of the algorithm looks very close to the core definition of any rate limiter, it becomes important to visualize what is happening here and implement it in an extremely efficinet and resourceful manner.

## Visualizing sliding window
Everytime we get a request, we make a decision to either serve it or not; hence we check the number of requests `nr` made in last `tw` seconds. So this process of checking for a fixed window of `tw` seconds on every request, makes this approach a sliding window where the window of size `tw` seconds is moving forward with each request. The entire approach could be visualized as follows

![Sliding window visualization](https://user-images.githubusercontent.com/4745789/78364339-eac01a80-75da-11ea-8f65-633fd779afac.png)

## The pseudocode

The core of the algorithm could be summarized into the following Python pseudocode.

```py
def is_allowed(key:str) -> Bool:
"""The function checks the number of requests served
"""
    # Fetch the rate limit configuration for the given key
    # the configuration holds the number of requests allowed in a time window.
    config = get_ratelimit_config(key)

    # Fetch the current window for the key
    # The window returned holds the number of requests served from the start_time
    start_time = datetime.now() - timedelta(seconds=config.time_window_sec)
    window = get_current_window(key, start_time)

    if window.number_of_requests > config.capacity:
        return False
    
    # Since the request could go through, register it.
    register_request(key)
    return True
```

A naive implementation of above pseudocode is pretty trivial but the challenge lies in making the implementation horizontally scalable, with low meomery footprint and low CPU utilization and low time complexity.

# Design
Now we take a deeper look in the design of this Sliding window rate limiter. We shall dive deep into low level data models, data stores, data structures and high level contructs to ensure horizontal scalability.

## Deciding the datastores and schema
Picking the right datastore for the use case is extremely important. The kind of datastore we choose determines the performance of the system like this.

### Rate Limit Configuration
The rate limit confguration could be stored in any relational or non-relational database. We would not wat to store the configuration in memory because if memory is volatile (and not disk-backed) then in case of machine failure we would loose all the configuration.

### Requests Store
The requests store will hold the requests serverd against each key. The most frequent operations on this store will be
 - registering requests served against each key (write heavy)
 - summing all the requests server in a given time window (read and compute heavy)

We chose an in-memory store for storing requests because
 - we need fast aggregation (summation) of items in window
 - read and write both are very frequent, and
 - it is okay to loss request count data since the time window is usually small enough

To gain deeper understanding of the core implementation we will not use existing in-memory store like Redis, but we shall manage the data using raw composite types provided by the language.

## Schema

### Rate Limit Configuration
To keep things simple the rate limit configuration will be created against a key

We assume that we are using a SQL based database like Postgres or MySQL; schema for Rate Limit Configurtation will look like this

```
Table: configuration
Columns:
 - key: char(128)
 - time_window_sec: int
 - capacity: int

Primary Key: key
```

`key` is the unique key for which the rate limit is to be defined. If the ratelimit is to be applied per user then key becomes user id, if per access token then key holds the access token. For a generic rate limiter the key is something on which the defined limit will ve applied.

## Request Store

A request store is a simple Ordered dictionary that holds.
Here we assume the finest granularity we work is is `seconds`.

## Implementation
Now we implement all the helper functions we saw in pseudocode.

### Getting the ratelimit configuration

### Getting current window

### Registering the request

## Potential issues and performance bottlenecks
 - atomic counters
 - sharding

# Scaling the system using Golang and Redis
arlt added.

# References
 - [Rate-limiting strategies and techniques](https://cloud.google.com/solutions/rate-limiting-strategies-techniques)
