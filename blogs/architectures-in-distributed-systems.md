While designing a Distributed System, it is essential to pick the right kind of architecture. Usually, architectures are evolving, but picking the right one at the inception could make your system thrive.

So, here are 4 common architectures in Distributed Systems

## Client-server

To render some information to the end-user, the client contacts the server (holding the data) with a request; the server sends back the data requested. The client is smart enough to understand how to request the data, post-process it, format it, and then serve it to the end-user.

This kind of architecture is not common in our day-to-day web applications. Still, it is prevalent when multiple services share a common database (server) and request data directly from the database.

## 3-tier

This is one of the most widely used topologies out there. Unlike client-server architecture, the clients in a 3-tier architecture are not smart and are stateless. This architecture introduces a middle layer holding the business logic. The client talks to the business layer, and this business layer talk to the server (holding the data).

Most of the web applications are 3-tier applications where your client (browser) talks to the business layer (webserver), which in turn queries the server (database) for the data. The business layer processes and formats the data (optional) and sends it back to the client. The client does not know how the data is being fetched from the server, making it stateless.

## n-tier

As an extension to the 3-tier architecture, the n-tier application is where your middle layer (business layer) talks to another service to get information. This is typically seen when there is multiple independent business logic in the system.

A classic example of an n-tier architecture is Microservices based architecture. Each service is responsible for its information, and the service communicates with other services to get the required data. Thus, a 3-tier application typically evolves into an n-tier application.

## Peer-to-peer

Peer-to-peer architecture is typically a decentralized system wherein no special machines hold all the responsibilities; instead, the responsibility is split across all the machines equally. The peers act as both clients and servers, and they communicate with each other to serve the request.

A couple of popular examples of P2P architecture are BitTorrent and Bitcoin networks. The n-tier architecture can optionally evolve into a P2P, but this evolution is not that popular. Usually, going P2P is a choice that is made during the inception of the service.

# References
 - [Distributed Systems - Wikipedia](https://en.wikipedia.org/wiki/Distributed_computing)
