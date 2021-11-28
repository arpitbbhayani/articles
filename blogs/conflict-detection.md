Every [multi-master replication](https://arpitbhayani.me/blogs/multi-master-replication) setup comes with a side-effect - Conflicts. Conflict happens when two or more database accepts conflicting updates on the same record. We say that the updates are conflicting when we are unable to resolve them to one value deterministically. In this essay, we talk about conflicts and understand what they are, how to detect them.

# Conflicts

Say we are building an online book store allowing users to purchase books at the click of a button. Like any e-commerce application, even ours has a _Shopping Cart_, which acts as a staging area for everything the user shops for. The user likes a book, adds it to the cart, and proceeds to pay once the shopping is done, proceed to payment. When a user adds a book to the cart, this operation can never be forgotten or rejected - as it will result in loss of revenue and a very poor user experience.

Say the user had books `B1, B2, B3` in the cart already, and this state of the cart is consistent in both the master nodes `Master 1` and `Master 2`. Say the user just added book `B4` to the cart, and this request went to `Master 1` which makes the local state of `Master 1` to be `B1, B2, B3, B4`, while `Master 2` continues to remain at `B1, B2, B3`.

Now, say the user added another book `B5` to the cart, and this request went to `Master 2`. The request reached `Master 2` before the changes from `Master 1` got a chance to be propagated. Since the master node will accept the write the local state of `Master 2` becomes `B1, B2, B3, B5` while state of `Master 1` is `B1, B2, B3, B4`.

![Conflict in real world - shopping cart](https://user-images.githubusercontent.com/4745789/143672208-5be61867-13ba-41dd-bae5-d3f856512d54.png)

Thus, we have two versions of the same shopping cart. When the two master nodes syn, they will detect a conflict that needs to be resolved. The resolution to this conflict is not as simple as replacing one with the other because replacement will lead to the loss of information.

The correct way to address this situation is that we will have to merge the two versions of the cart such similar to the set union. This is a classical case of Conflict Detection and Resolution, and the possible resolution strategy depends on the application and context.

In the above example, we saw a custom conflict resolution strategy in a real use case, but resolving conflicts is not always possible. For example, when two users book the same seat for the same movie, the requests go to two different Masters, and both successfully acknowledge the user confirming the seat. Thus, in this case, the same seat for the same movie show was allotted to two different users. But, since we already sent the confirmation to the user, there is no way to resolve this conflict without giving one of the users an extremely poor experience.

# Conflict Detection

Detecting conflict is simple when we have a single Master node, given that we can serialize all the writes going through it - the second write waits while the first one executes.

But when we have a multi-master setup, all the Master nodes can accept the writes and successfully apply them to their copy of data. When the changes [asynchronously](https://arpitbhayani.me/blogs/replication-strategies) propagate to other Master nodes, the conflict is detected. Given that both the writes requests were successfully accepted and applied, there is no way to communicate the conflict to the client.

![Conflict Detection - Async Replication](https://user-images.githubusercontent.com/4745789/143669401-7dbe6429-a802-496a-83ec-aafc58ca2989.png)

Given that it becomes tough to do something after we detect a conflict when the master-master replication is asynchronous, a possibly easier way out would be to make replication [synchronous](https://arpitbhayani.me/blogs/replication-strategies). In this setup, when one of the Master nodes accepts write, let is successfully apply to its own copy of data and synchronously propagate the write to other Master nodes before responding to the client.

![Conflict Detection - Sync Replication](https://user-images.githubusercontent.com/4745789/143669672-51fcf264-97df-434e-940b-f77e3bfd3f2a.png)

Although this approach solves the problem of detecting conflicts and getting a chance to resolve them, it makes the setup lose its main advantage of allowing multiple masters to accept writes in parallel.
