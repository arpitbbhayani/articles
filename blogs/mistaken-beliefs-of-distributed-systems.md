The only way to infinitely scale your system is by making it distributed, which means adding more servers to serve your requests, more nodes to perform computations in parallel, and more nodes to store your partitioned data. But while building such a complex system, we tend to assume a few things to be true, which in reality are definitely not.

These mistaken beliefs were documented by [L Peter Deutsch](https://en.wikipedia.org/wiki/L._Peter_Deutsch) and others at Sun Microsystems and it describes a set of false assumptions that programmers new to distributed applications invariably make.

## Myth 1: The network is reliable;

No. The network is not reliable. There are packet drops, connection interruptions, and data corruptions when they are transferred over the wire. In addition, there are network outages, router restarts, and switch failures to make the matter worse. Such an unreliable network has to be considered while designing a robust Distributed System.

# Myth 2: Latency is zero;

Network latency is real and we should not assume that everything happens instantaneously. For every 10 meters of fiber optic wire, we add 3 nanoseconds to the network latency. Now imagine your data moving across the transatlantic communications cable. This is why we keep components closer wherever possible and have to handle out-of-order messages.

# Myth 3: Bandwidth is infinite;

The bandwidth is not infinite; neither of your machine, or the server, or the wire over which the communication is happening. Hence we should always measure the number of packets (bytes) of data transferred in and out of your systems. When unregulated, this results in a massive bottleneck, and if untracked it becomes near impossible to spot them.

# Myth 4: The network is secure;

We put our system in a terrible shape when we assume that the data flowing across the network is secure. There are many malicious users that are constantly trying to sniff every packet over the wire and de-code what is being communicated. So, ensure that your data is encrypted when at rest and also in transit.

# Myth 5: Topology doesn't change;

Network topology changes due to software or hardware failures. When the topology changes, you might see a sudden deviation in latency and packet transfer times. So, these metrics need to be monitored for any anomalous behavior and our systems would be ready to embrace this change.

# Myth 6: There is one administrator;

There is one internet, and everyone is competing for the same resources (optic cables and other communication channels). So, when building a super-critical Distributed system, you need to know which path your packets are following to avoid high-traffic competing areas.

# Myth 7: Transport cost is zero;

There is a hidden cost of hardware, software, and maintenance that we all bear. If you are using a public cloud-like AWS, then the data transfer cost is real. This cost looks near zero from a bird's eye view, this cost looks near zero, but when you are operating at a massive scale, the cost grows massive.

# Myth 8: The network is homogeneous.

The network is not at all homogeneous. The packet that you have transferred may go from Fibre optic cable to a 4g band, to a 3g overlay, and then to the user's device. Even within your VPC, there may be different wires, network cards connecting different components. So, to build a robust system, measure and do not assume.

# References

- [Fallacies of distributed computing](https://en.wikipedia.org/wiki/Fallacies_of_distributed_computing)
