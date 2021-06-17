The only way to infinitely scale your system is by making it distributed, which means adding more servers to serve your requests, more nodes to computed in parallel, or more storage nodes to store partitioned data. But while building that, we tend to assume a few things to be true, which in reality are definitely not.

These fallacies are a set of assertions made by [L Peter Deutsch](https://en.wikipedia.org/wiki/L._Peter_Deutsch) and others at Sun Microsystems describing false assumptions that programmers new to distributed applications invariably make.

# Myth 1: The network is reliable;

No. The network is not reliable. There are packet drops, connection interruptions, and data corruptions when it is transferred over the wire. In addition, there are network outages, router restarts, and switch failures. Such an unreliable network has to be considered while designing a robust Distributed System.

# Myth 2: Latency is zero;

Network latency is real. Do not assume everything happens instantaneously. For every 10 meters of fiber optic wire, we add 3 nanoseconds to the network latency. Now imagine your data moving across Transatlantic communications cable. This is why we keep components closer wherever possible.

# Myth 3: Bandwidth is infinite;

A big no. The bandwidth is not infinite; neither of your machine or the wire over which the communication is happening. Therefore, the metric which is least tracked is packets transferred in and out of your systems. This typically results in massive bottlenecks, and if relevant metrics are not tracked, it will be impossible to spot them.

# Myth 4: The network is secure;

Security is critical, assuming that data that flows across your network is secure and will put you in terrible shape. This is because many malicious users are trying to sniff every packet over the wire and decide what is being communicated. So, where your data is at rest or in transit, encrypt it.

# Myth 5: Topology doesn't change;

Network topology changes due to software or hardware failures. When the topology changes, you might see a sudden difference in latency and packet transfer times. Be ready to embrace such a sudden change while building a robust Distributed System.

# Myth 6: There is one administrator;

There is one internet, and everyone is competing for the same resources (optic cables and other communication channels). So, when building a super-critical Distributed system, you need to know which path your packets are following to avoid high-traffic competing areas.

# Myth 7: Transport cost is zero;

There is a hidden cost of hardware, software, and maintenance that we all bear. If you are using a public cloud-like AWS, then the data transfer cost is real. This cost looks near zero from a bird's eye view, this cost looks near zero, but when you are operating at a massive scale, the cost grows massive.

# Myth 8: The network is homogeneous.

The network is not at all homogeneous. The packet that you have transferred may go from Fibre optic cable to a 4g band, to a 3g overlay, and then to the user's device. Even within your VPC, there may be different wires, network cards connecting different components. So, to build a robust system, measure and do not assume.

# References

- [Fallacies of distributed computing](https://en.wikipedia.org/wiki/Fallacies_of_distributed_computing)
