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

# Data models

## Capacity
The capacity is usually defined per API or Per user or per access token and is usually stored as a configuration in a persistent data store.

The capacity (the limit) is usually defined as a configuration and is defined in terms of number of requests in a time window.

If the request count exceeds the number agreed by the service owner and the user (in a decided window time), the rate limiter blocks all the excess calls(say by throwing exceptions). The user can be a human or any other service(ex: in a micro service based architecture)

Rate limiting is important not only for incoming requests but also for outgoing requests.

# The sliding window algorithm
The core of the algorithm comes from a very basic heuristic intuition where we

# Potential issues and performance
 - atomic counters
 - sharding

# Scaling the system using Golang and Redis
arlt added.

# References
 - [Rate-limiting strategies and techniques](https://cloud.google.com/solutions/rate-limiting-strategies-techniques)
