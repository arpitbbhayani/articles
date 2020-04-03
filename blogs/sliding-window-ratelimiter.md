A rate limiter is an engine that ensures your are neither serving nor invoking a lot of requests in a short span. A production system has a capacity if it receives more requests that its capacity, the system fails and goes down. To prevent this a rate limiter acts as a gatekeeper and regulates the number of requests that flows into your system and once the number of request reaches capacity all other requests are discarded.

protect themselves from excessive use (weather intended or unintended) to maintain service availability
defensive measure for services

Why it is important to rate limit

 - Preventing resource starvation
 - Managing policies and quotas
 - Avoiding excess costs
 - Controlling flow

There are lots of algorithms for rate limiting: ---, -- , --- and here we dive deep into Sliding window based approach to rate limit.

# Temrinologies and 
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
