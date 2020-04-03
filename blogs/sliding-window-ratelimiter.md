A rate limiter restricts intended or unintended execssive usage of a system by regulating the number of requests made to/from it by discarding the surplus ones. In this article we dive deep into a intuitive and heuristic approach for rate limiting using sliding window; other approaches include "", "" and "".

Rate limiting is usually applied per access token or per user or per region/ip. For a generic rate limiting system this is abstracted by a `key` on which the limit will be configured; the key could hold any of the aforementioned value. The limit is defined as the number of requests `number_of_requests` allowed within a time window `time_window_sec` (defined in seconds).

# The algorithm
The algorithm is pretty intuitive, and could be summarized as follow

> If the number of requests served on key `key` in last `time_window_sec` seconds is more than `number_of_requests` then block or else the the request go through and update the counter.

Although the above gist of the algorithm looks very close to the core definition of any rate limiter, it becomes important to visualize what is happening here and implement it in an extremely efficinet and resourceful manner.

## Visualizing sliding window
Everytime we get a request, we make a decision to either serve it or not; hence we check the number of requests `number_of_requests` made in last `time_window_sec` seconds. So this process of checking for a fixed window of `time_window_sec` seconds on every request, makes this approach a sliding window where the window of size `time_window_sec` seconds is moving forward with each request. The entire approach could be visualized as follows

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
    start_time = int(time.time()) - config.time_window_sec
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

### Configuration Store
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

### Configuration Store
An SQL schema, for using a database likePostgres or MySQL, for Rate Limit Configurtation would be as follows

```
Table: configuration
Columns:
 - key: char(128)
 - time_window_sec: int
 - capacity: int

Primary Key: key
```

`key` is the unique configuration key for which the rate limit is to be defined. If the rate limit is to be applied per user then key becomes `user:user_id`, if per access token then key holds the `token:access_token`. For a generic rate limiter the key is something on which the defined limit will be applied.

This could well be stored in a persistent key value NoSQL store like MongoDB or DynamoDB.

## Request Store
A request store is a nested dictionary where outer dictionary maps the configuration key to inner dictionary while the inner dicitonary maps the epoch second to the request counter. The inner dictionary primarily holds the number of requests serverd during the corresponding epoch second. This in memory structure will help us update and aggregate faster.

![Requests store for sliding window rate limiter](https://user-images.githubusercontent.com/4745789/78384914-b0657600-75f8-11ea-8158-981ac3ecd46d.png)


## Implementation
Now that we have defined and designed the data store it is time that we implement all the helper functions we see in the pseudocode.

### Getting the rate limit configuration
Getting the rate limit configuration is a simple get on the configuration store. If it is SQL then a simple `SELECT` on `key` would do the job, if NoSQL then make approriate call on the key to get the detailed configuration.

Since the information does not change often and making a disk read everytime is expensive, we cache the results in memory for faster access.

```py
class Configuration:
    def __init__(self, capacity, time_window_sec):
        self.capacity = capacity
        self.time_window_sec = time_window_sec

    @classmethod
    def from_resultset(cls, r)
        return cls()

def get_ratelimit_config(key):
    results = sql.execute("""
        SELECT time_window_sec, capacity from configuration
        WHERE key = %s;
    """, key)
    return Configuration.from_resultset(results[0])
```

### Getting current window

```python
from collections import defaultdict

store = defaultdict(lambda: defaultdict(int))

class Window:
    def __init__(self, number_of_requests):
        self.number_of_requests = number_of_requests

def get_current_window(key, start_time):
    ts_data = store.get(key)
    if not key:
        raise Exception("invalid key")
    
    total_requests = 0
    for ts, count in ts_data.items():
        if ts > start_time:
            total_requests += count
        else:
            del ts_data[ts]

    return Window(total_requests)
```

### Registering the request

```python
def register_request(key):
    current_time = int(time.time())
    store[key][current_time] += 1
```

## Potential issues and performance bottlenecks

### Atomic counters

## Scaling the solution

### Single instance of in-memory store

### Horizontal scaling

## High level design

## Deploying in production
Using golang and Redis
arlt added.

# References
 - [Rate-limiting strategies and techniques](https://cloud.google.com/solutions/rate-limiting-strategies-techniques)
