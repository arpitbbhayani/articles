A rate limiter is an engine that ensures your are neither serving nor invoking a lot of requests in a short span. A production system has a capacity if it receives more requests that its capacity, the system fails and goes down. To prevent this a rate limiter acts as a gatekeeper and regulates the number of requests that flows into your system, while discarding the surplus.

The capacity (the limit) is usually defined as a configuration and is defined in terms of number of requests in a time window.

There are lots of ways 

A rate limiter is a tool that monitors the number of requests per a window time a service agrees to allow. If the request count exceeds the number agreed by the service owner and the user (in a decided window time), the rate limiter blocks all the excess calls(say by throwing exceptions). The user can be a human or any other service(ex: in a micro service based architecture)

Rate limiting is important not only for incoming requests but also for outgoing requests.

# The sliding window algorithm
The core of the algorithm comes from a very basic heuristic intuition where we

# Potential issues and performance
 - atomic counters
 - sharding

# Scaling the system using Golang and Redis
arlt added.
