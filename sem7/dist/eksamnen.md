
# TODO

  - Lav FIFO opgave i exercise5
  - Læs mere om gossip architecture.
  - Read about transactions 17(LOW)
  - Lav opgave om Chord

# Distributed Mutual Exclusion

## Notes

**Mutual exclusion** is an algorithm that ensures that one and only one process can access a resource at a given time.
Some examples include:

  - Storage
  - Printing
  - Coffee machines
  - Wireless or wired communication

### System Model

A computer system is a tuple with a set of states, an initial state, a set of messages, and a transition function.
We will count time as the number of messages/events, as use this as a measure of performance.

Messages can be sent in two different ways.
**Asynchronous** where messages arrive with arbitrary delays, and where processing time is unknown.
**Synchronous** hard or known limit on delays and a known drift.

### Mutex Algorithm

We can set up some requirements for the mutex algorithm

  - **Safety** is when at most one process is given access.
  - **Liveness** dictates that requests for access are eventually granted.
  - **Ordering/fairness** requires that the ordering of requests should be the order in which they are granted.

And some properties

  - **Fault tolerance**, what happens when a process chrashes or a message is lost. Does that take the whole system with it.
  - **Performance**
    - **Message Complexity** is how many messages are required to lock/unlock mutex.
    - **Client Delay** time from a request to the grant.
    - **Synchronization Delay** time from release of lock to next grant.

### Central Server Method

Request for at grant are sent to a central server, which then grants according to a queue.
This is a save and liveness method, however because of the travel time it is not ordered.

This fails if either a mutex holder or the server fails.

### Token Ring Method

Grants are sent in a ring, where each process knowns its next neighbour.
To lock the mutex, we just wait by forwarding the message.

This is a save and liveness method, however does not uphold the ordering of "requests".
It also fails if just one processor fails.
It also takes up a constant amount of network traffic.

### Ricart and Agrawala's Algorithm

Ordering of events is ensured with a lamport clock.

It works by having processes send requests to all other processes.
Everyone not holding the lock will then grant it access, but a locked process will wait giving access til it is done.

This does achieve ordering, however it will fail if just one of the processes fails.

### Meakawas Algorithm

We do not need everyone to say yes, just some subset.
However we must ensure that all subsets have some overlapping processes.
Therefore processes end up voting for each other.

However it can deadlock, with three processes.

### Detection with Heartbeats

Assume a transmission or beat every T seconds.
Therefore a process can be assumed dead if not observed in the last `T + D` seconds, where `D` is the transmission delay.

### Election

Often we need to chose a process for a central role.
Such as the server in mutual exclusion.
This is done with election, where a process *calls the election*.

Each process has a chosen elected value, which when undefined is this wierd grounding symbol.

We have some requirements for election:

  - **Safety**: a participating process has chosen a `undefined` process or a non-crashed process `P`.
    Here `P` must have the largest identifier. Here `P` must be the same for all `p_i`'s.
  - **Liveness**: all processes must either crash or select some process.

An *identifier* is just some general value for each progress, which must give some total ordering.

#### Ring Based Election

Again we have processes in a ring.
If assuming that no failures occur, we can start the election.
At first no proccess is marked as participating, but a process can call for election by adding ifself as a pariticipant and sendings it's id in an election message.
When receiving a process will just forward if the message identifier is larger than itself.

Because this works by sequentially sending messages (requiring at most `3*N-1` messages), this is not very fast.
It is also very prone to failure.

#### Bully Algorithm

This is different in that each process knowns all other processes with higher id's, and can talk to such processes.

Processes that know they are the highest can send a `coordinator` message to all lower processes.
If it knows higher processes it can send a `election` message, and wait for an answer.
If no answer comes it will consider itself a coordinator and send `coordinator` message to all lower processes.
It it receives an answer, it will wait for a `coordinator` message.

This does not work if we replace crashed processes with new processes that have the same id.
Then we can end up with processes electing themselves as coordinator.

Also in the worst case, where the lowest process detects a failure, the algorithm requires `O(N^2)` messages.

# Multicast

Here we assume static and closed groups of processes.

In the tcp/ip stack we have dedicated ip address ranges for multicasting.
However it may be the case that hardware does not support multicast, and we actually need to each receiver manually.
UDP also has the problem that messages are not ordered and retransmission are not done.

We can setup some properties for reliable multicast algorithms.

  - **Integrity**: requires that all messages are unique and are only delivered once.
  - **Validity**: if a process multicasts message `m`, it will eventually also deliver `m`.
  - **Agreement**: if one process delivers message `m`, then all other processes also deliver `m`.
  - **Uniform agreement**: if a process, whether it is correct or not, delivers a message `m`, then all correct processes will eventually deliver `m`.

## Basic Multicast

Each sender just sends the message to all other participating devices, including itself.

This has the problem that the sender might fail and send message to a subset of other devices.
Also if using a reliable send mechanism, there will be an ACK explosion.

## Reliable Multicast

We introduce a store where we can lookup messages.
Then when we multicast a message, we `b-multicast` to multicast to other devices.
If they receive and they have not seen the message before they multicast the message to everyone else, and delivers to the application.

This works, however is very expensive.

## Reliable Multicast over IP

Here we piggyback acknowledgements in the messages itself, instead of sending acks.
Then when we detect that we miss packets, we use `NACK`.

This is achieved by each process maintaning a sequence number for each other process (including ifself).
This is then sent along with every message.

Then each process knows about the next expected message from each device, and can NACK then this skips.

Practical problem is that we cannot hold infinite sequence numbers and maps of every message ever.

Also agreement only works if we keep sending messages forever.
This is because we only detect failed messages, when the next messages comes.

## Orderings for Multicast

  - **FIFO ordered**: all messages from `p_n` are received by `p_k` in the order they are sent by `p_n`.
  - **Total ordered**: all messages are received in the same order on each process.
  - **Causally ordered**: if `p_n` received `m_1` before `m_2`, then `m_1` happened before `m_2`.

We know that casual order implies FIFO order.
These two are only partial order.

Total ordering does not imply FIFO og casual, as the order in which everyone agrees can be anything.
We can therefore also have hybrid, such as *FIFO-total*.

## Implementing Total Ordering

We can implement total ordering with *sequencer*, as follows.
A single central server is chosen as the sequencer.
Then multicasted messages are held in a buffer at each process until they are instructed to deliver this message by the sequencer.

This means that the sequencer has complete control over the ordering of messages, enforcing at total order.

If messages are sent to the sequencer as FIFO, the ordering can be said to be casual.

Alternatively each process can try to aggree on a sequence number without a central process.
This can be done by letting each receiver propose sequence numbers to the sender.
The sender can then choose the largest, and return this to everyone.

## Implementing Causal Ordering

Here we utilize a vector clock to give message order.
We add one to our time each time we send a message, and include our vector in each of our messages.
That way if `a` receives a message `m` from `b`, we will save that message until we have seen all messages from `b` before `m`, and any message `b` has received before sending `m`.

# Consensus

We have looked at specific cases of agreeing.
Such as election, ordering, mutual exclusion.
Consensus is a generalization of this.

Here we consider the case that there may exist *byzentine* processes that try to screw with the consensus.
Here message signing can limit the harm done by such processes.
However, it is assumed that messages are not signed.

In the consensus problem we have some processes that each draw a value `v_i`.
Then after exchanging some message, they will each decide on a value `d_i`.
We have some requirements for this:

  - **Termination**: Each correct process will decide on a value.
  - **Agreement**: All correct processes decide on the same value.
  - **Integrity**: If all correct processes propose the same value, that value is also decided by all correct processes.
  - **Weak integrity**: The aggreed value must be a proposed by a correct process.

## With no Failures

When failures are impossible, we can just let each process send their `v_i` to everyone else, and then use a majority function to find the most common value.
Here Agreement and Integrity are ensured because of the same majority function on each process.
Termination is also guarantied by the multicast algorithm.

## Byzentine Generals

Three or more generals must decide whether to attack or retreat.
But one or more of the generals can be treacharous.

This differs from normal consensus, in that only one process chooses a value, that the others must agree or disagree with.

## Interactive Consistency

Here processes must agree on a vector off values, where each place in the vector represents the decided value of a process.
This is not covered by the slides, and is probably not that important.

## Consensus in a Synchronous System

We can get consensus in a synchronous system by using multiple rounds.
Here we let `f` be the maximal number of faulty (not Byzentine) processes.
Then we can reach consensus in `f+1` rounds.

In each round all processes send values not already sent, and accumulate received values.
In the end a decision is made from the accumulated values.

Given that this is synchronous we know that it will terminate.
Proof of correctness and thereby agreement and integrity:

> Assume, to the contrary, that two processes differ in their final set of values.
> Without loss of generality, some correct process p i possesses a value v that another
> correct process p j ( i ≠ j ) does not possess. The only explanation for p i possessing a
> proposed value v at the end that p j does not possess is that any third process, p k , say,
> that managed to send v to p i crashed before v could be delivered to p j . In turn, any
> process sending v in the previous round must have crashed, to explain why p k possesses
> v in that round but p j did not receive it. Proceeding in this way, we have to posit at least
> one crash in each of the preceding rounds. But we have assumed that at most f crashes
> can occur, and there are f + 1 rounds. We have arrived at a contradiction.

## Byzentine Generals in a Synchronous System

Here any process may decide to do random stuff, such as sending messages at the wrong time, sending from data, or just not sending anything.
It can be shown that this cannot be solved for `N = 3` or `N \leq 3 * f`.

The **Byzentine Integrity** requirement requires that if all non-failty processes start with a value, they all decide on that value.

If there is only one byzentine general, then we can just use majority vote to find a value.
However it there are ties, we find no solution.

There is also the king algorithm for cases where `N > 4 * f`.
Here each process takes turn at choosing the value for a round.

## Paxos

In a async setting we cannot guarantee that there is a solution.

In paxos once a majority agree on something there is consensus, which will eventually be known by everyone.
Here faulty communication is taken into account.

In paxos there are 3 roles for processes:

  - **Proposers**: propose values, to reach consensus on.
  - **Accepters**: contribute to reaching concensus.
  - **Learners**: who learn the agreed on value.

Nodes can have multiple nodes, or even all of them.
However they can not change these roles.

1.  First a proposer proposes a certian value with a prepare message to all accepters.
    These are sent with an ID, such as the timestamp is milliseconds.
2.  Then accepters will accept this if they have not promised to ignore this is.
    If they accept they promise to ignore any id lover than this.
    This is done with a promise message containing that id.
3.  If a proposer gets a majority of promise messages it will send accept-request with id and value to all or a majority of acceptors.
4.  If a accepter gets an accept-request with an ignored id, it will do nothing.
    Otherwise it will send an accept message with the value to all learners.

There are 3 milestones in this process.

  - A majority of accepters promise that no id over that some id can make it through.
  - A majority of accepters accept some id and value.
  - A majority of learners and proposers gets majority of accepts on some id. They then know that consensus is on the value.

There is some extra logic for when a value has already been accepted by a accepter.
Here the promise with also include the last accepted value and id.
The proposer must then create an accept-request with the value with the highest id.

# Replication

Employing replication can have some different advantages over just a single device.

  - **Performance**: Instead of everyone pulling from a single server, multiple servers can be employed to serve the same content.
    This can give major performance improvements.
  - **Availability**: A service should be available for close to 100% of the time.
    By using replication multiple services can together give a very high availability of a service.
    A second case where networks are split appart (such as a laptop on a train), replication can be used to keep a subset of the service available.
  - **Fault tolerance**: Data that is highly available is not always correct.
    Fault tolerance guarantees correct behavior up to some number of failing processes.

A basic model for a replicated system is one where multiple clients talk to a number of frontends.
These frontends can then talk to the service, via a set of replica managers.
This communication is all request response.

These replica managers are represented as state machines, meaning their state only depends on the operations that have been applied, such as write or read.
In general there are 5 stages in a single operation on replicated objests.

1.  **Request**: A frontend issues a request to one or more replica managers.
    This can happen either by sending to a single replica manager which will communicate with the other replicas, or with multicast.
2.  **Coordination**: Here replica managers must coordinate how to execute this request consistently, and whether it should be applied.
    They will also decide on the ordering of the request in regards to other requests. This comes back to the orderings from before.
    Most systems use FIFO ordering.
3.  **Execution**: The managers execute the request. This can be done *tentatively* such that they can undo the effects later.
4.  **Agreement**: The managers reach consensus on the effects of the request to be committed..
5.  **Response**: One or more managers send a response to the frontend. This can use majority voting to combat Byzentine failures.

## Consistency

We want to make sure that our whole system functions like it would if there was only a single server.
For example if client 1 writes to `x = 1` and `y = 2`, then it makes no sense if another client first reads `y = 2` and then `x = 0`.
This is because `x` is written before `y`, so given that `y` is read correctly `x` should also be.

Here we introduce the property that the system is *linearizable*.
A replicated shared object service is then linearizable if there is some interleaving of operations issued by all clients, such that
  - we arrive at a (single) correct copy of the object,
  - and the order is consistent with real time.

However this is very hard because the real-time requirement requires accurate synchonized clocks.
Therefore the weaker *sequential consistency* captures some of the same order requirements without using a real-time clock.
It requires that
  - we arrive at a (single) correct copy of the object,
  - and the order in the interleaving is consistent with the order in which the induvidual clients executed operations in.

This means that operations can be shuffled around as much as we, as long as we respect the ordering of the induvidual clients.

## Passive Replication

Here we choose a single manager which talks to all frontends.
After executing the request, it will push the update to all other managers.

If the primary crashes then operation will happen on a backup.

Does not handle Byzentine very well.

## Active Replication

Here the frontend sends the request to all managers with total ordered reliable multicast.
After executing and updating, each manager will respond with the result.
Because of majority voting we can handle up to `(n/2) - 1` Byzentine failures.

Here the frontend waits on the response before sending the next request.
Therefore FIFO ordering is ensured in regards to the frontends.

If clients can talk together we would need to use a casually totally ordered multicast.

## Gossip Framework

Here data is replicated between managers periodically.
Therefore we only need to read or write to a single manager.

Here we can guarantee some relaxes consistency in that
  - operations are eventually applied with some specific order,
  - and clients can receive outdated data but newer older than the clients current data.

Here reads are causually ordered while writes can be causal order, total-causal order, or immediate order.
Immediate order updates are applied consistenly in order to any other update.
Here causal order is the cheapest to implement.

Vector clocks are used to ensure this, with each replica tracking the number of unique updates

# Distributed Storage

## GFS

Has a single *GFS master* which contains the file namespace, pointing filenames to chunks.
Will return the chunk handle and location to the client.

The client can then request the clunk from one of the many *chunk servers*.

Because filenamespace are kept on master, mutations of this is atomic.
The master also handles replica management, allocating new chunks, or reallocating when there is not enough replication.
Also handles garbage collection and balancing of chunks.

Log and state of master is also replicated in stable storage, such that it is fast and easy to recover.
There are also *shadow masters*, providing read only access.
External services can start new master if it detects failure in main master.

Writes are done by having the master select a primary replica, which will determine the order things are applied in.
This works like passive replication only that data is written to the all the replicas by the client, but the operation is only given to the primary.
One should note that multiple writes at the same location can not be applied together, as appends can.

## Chubby

For very small files such as locks etc.
Can be used for stuff like master election, where processes write to file, and the one is written is the master.
Because files are small, there is whole file read and write, instead of chunks.

Communication with clients happen through a master, which then forwards onto replicas.
Clients can find the master using DNS, or with other non-masters refering to master.
Clients will keep using a master until a negative answer.

Reads are handled by master, while writes are done like paxos.

*Sessions* are mentained between a master and client, with keep alive(eg. 12 seconds).
If session is lost server releases handles held by client.
If a client does not get a renew on lease, session is *in jeopardy*.
Here cache is cleared, and a grace period is done before trying again.

Clients cache content of files, to reduce traffic.
Invalidation is then piggybacked on the keep-alive. Flush of cache is ack'ed in lease reneval.

Master relection is done with paxos, and updated in DNS by new master.

## BigTable

DIstributed storage of table.
Works kind of like a map:

```haskell
(String, String, Int64) -> String -- (row, column, time) -> content
```

In google it is used to store

  - Analytics, where each row is a user.
  - Earth, where each row is a location and column in a source.
  - Personlized serach, where row is user and column is action type.


A *tablets* is a set of rows, with a size of around 200Mb.
These can be merged of split depending on their size.
Each tables is stored by a *Tables server*, similar to a gfs chunkserver.
Storage is done with the *Sorted String tables* file format from GFS.
Provides atomic row access.

Like GFS also uses a single master, and a set of servers.
Master and server use chubby for lock files etc, and GFS for storage of table data and logs.

Searching is done with B+tree index.
Clients search this index and caches tablet locations.

# Big Data Analytics

The 4 v's

  - **Volume**: the large scale of data collected and processes.
  - **Velocity**: the timeliness?? of data and analysis.
  - **Variety**: different types of data, semi-structured or unstructured (such as text).
  - **Value**: a lot of data, but with low density.

Often when data is collected we need to do a large amount of processing to make it usefull.
With the massive volumes of data this is not practical on a single computer.

Therefore we develop new methods for storing (GFS, NoSQL), and programming/processing (Map reduce and Pregel).

Sawzall is a bit like map reduce, only in that there are many filter tasks, and then a single aggregator.

## Map Reduce

Inspired by the two functions from functional programming.
Here we as a programmer must introduce two functions:

  - **Map**: takes input data and produces `(key, value)` pairs.
  - **Reduce**: takes all values with the same key and produces a result.

In between the map and reduce we have a *shuffle phase* which collects the results up so tuples with the same key are together.
This shuffle phase involves the network.

For the execution we introduce a *master* which assigns the function applications to workers.
When a map is done the result is written to disk, and the location is returned to the master.

The master must take into consideration the

  - **Locality** of the data in regards to the worker.
  - **Granularity** in that the number of map and reduce tasks should be much higher than the number of workers.
  - **Stragglers** in that large systems always has workers that are slower, and the master should schedule around this.
  - **Pipelining** can we start reducing while still mapping other data?
  - **Failures** when a worker fails, the job should be done by somebody else.

When the master fails there is not much to do, so we terminate the whole job.

## Spark

Lets programmers write parallel computations easily with high level operations, without having to handle work distribution and fault tolerance.
However does not make it easy to handle memory, and is therefore hard to reuse results (as in graph algorithms, pagerank, regression).

Here we can use RDD or Resilient Distributed Datasets.
Here datasets are saved in immutable partitioned collections of records.
This is then used to store intermediary results.
Also provides operators like map, filter and join.

RDD have dependencies, where rows depend on other rows.
With map, union and joins give *narrow dependencies* where each row in the operands is used by at most one row in the result.
*Wide dependencies* is when this is not true, and happens for `groupByKey`.

## Pregel

Like spark/RDD but tailored to graph computations.
Also has a in memory store to keep intermediary results.

The computational model is *vertex-centric* where program are a sequence of iterations, where in each a vertex can change state or send messages to other vertices.
The algorithm halts when all vertices want to halt.
Here it's beneficial to also have the number of vertices be much larger than the number of processes.

Vertices start out in a active state, and can deactivate by voting to halt.
They can be reactivated when they get a message.

Page rank is a graph algorithm.

Also uses a single master many workers thing.

# Blockchains

**Merkle trees** are trees build on hashes.
So leaves are hashes of the content, and internal nodes are hashes of children.
Used by git for example.

For a binary merkle tree, calculating the root takes `2N` hashes.

**Blockchain** works like this tamper proof linked list.
Given that it is distrubuted, it has some nice properties:

  - **Consistency**: Information is held of shared distributed database.
  - **Robustness**: No centralized version that can be hacked.
  - **Availability**: Data is stored by millions of computers and can be verified by everyone.

All nodes contain a full copy of the blockchain, and validate and relay data.

We can prevent double spending by disallowing forks and checking if there is anough money.
How do we choose the newest head, we can't use paxos because hacker can just create 1000 new identities.
Creating identities is cheap, we need something expensive (like hashing (spoiler (triple parenteser, nice))).

(*Nakamoto Consensus*) Blockchain has the rule that the longest blockchain has consensus.
Therefore we can ignore all chains that are shorter than my own.
By making it hard to add blocks, we trust blocks that are burried.

By making it hard to add blocks, hackers have a hard to make a competing fork as they have to work against all other miners.
To make it hard we use a nonce on each block.
Then the hash of the block must start with x amount of 0's.

A bitcoin user is someone who can transfer money, and has a wallet or identity.
This identity is just a key pair.

A transaction has multiple inputs and outputs (with distribution) and then signatures of inputs.
More generally they use scripts which often contain signatures, but can also be a small non-turing complete program.
These transactions are then stored in a merkle tree, with the root being in the block.

Each transaction has a small difference in the ingoing and outgoing money.
This is the fee to the miner who finds the nonce.
Also miners get some bitcoin for each nonce they find.

## Smart Contracts

Bassicly an extension of the challenge scripts in the bitcoin transactions.
Extended in ethereum.

Here it is turing complete, but the script runs on gas, which can run out.

# Peer-to-peer networks

**Overlay network** is a set of nodes and links built on top of a existing network.
This overlay network can add features that are not present in the underlying network, such as extra service, routing, multicast or enhanced security.

Here are some types of overlay networks

  - **Distributed hash tables** (application needs): offers a service where one can map keys to values.
  - **Peer to peer file sharing** (application needs): offers easier addressing and routing to support downloading of files etc.
  - **Content delivery networks** (application needs): provides replication, caching and placement strategies for delivering content.
  - **Wireless and adhoc networks** (Network style)
  - **Multicast** (extra features)

The classic client server architecture has some limitations in terms of scalability and reliability.
Here one possible solution is peer to peer.
Peer to peer solves many problems but is often more complicated.
Because networks are often public it is hard to stop some people from exploiting the rest (*free-riding*).

Peer to peer networks can be descibed as a set of automonous entities (peers) that are able to auto-organize and share some distributed resources.
Most peer to peer networks can be put in 3 categories:

  - **Distributed computing**
  - **File sharing**
  - **Collaborative applications**

With filesharing there is a very common set of primitives: join, publish, search and fetch.

## Napster and Centralized Peer to Peer

Napster allows users to download free music over the internet.
Because it is impossible for the napster server to contain all the content on one machine, napster employs a peer to peer system to store music files.

However for simplicity napster has a centralized index server, where users can find which peer has which files.
This has the advantage of allowing easier and nicer search and indexing, at the cost of robustness and scalability.

## Unstructured Peer to Peer

Used by the gnutella file sharing program.
Works which query flooding, where a client ask other known clients about a file and they ask their known clients and so on.
When the file is found, the client can directly contact the file holder and download the file (via HTTP).
Here known clients are established from a bootstrap node.

HTTP has the advantage of being allowed by many firewalls, and can do partial file transfer.

Gnutella has the advantage of being totally decentralized, and thus very robust.
However its flooding nature does not make it very scalable.
And free-loading can download but no answer queries.

A newer protocol, *fasttrack*, tries to solve some of these issues.
Here some peers are designated as *supernode* (or *ultrapeers*).

In fasttrack when joining the client contract a supernode.
It can use this node to publish files.
Then when querying, the client only asks the supernode which will flood the request to all other supernodes (not normal peers).
Peers with enough reputation can themselves become supernodes.

### Searching

There are methods for making search faster, instead of just flooding.

  - **Expanded ring search**: Repeatedly flood query, but with increasing time-to-live
  - **Random walk**: Start a number of walkers that take a random path through the overlay network.
  - **Gossiping**: Flood request with a certian probability, thereby flooding the network much like a virus (therefore also called *epidemic protocols*.

## Structured Peer to Peer

Structured peer to peer has some advantages in that the algorithm can take assumption about the structure and therefore give lower complixity bounds.
This gives a low message overhead, and shorter retrieval times.
However these structures are much harder to mentain and is often costly in very dynamic environments.

Here unstructured is much better at self-organization, and is more resilient to node failure.
However it can guarantee much for the lookup times for objects, and are prone to messaging overhead, thereby hurting scalability.

### Chord

Chord is a protocol and algorithm for a distributed hash table.
It structures the different peers in a ring, each knowing its successor and predecessor.
The ring represents the key space, with each peer being responsible for a range of keys (from the predecessor to ifself).

To keep this structure intact, a periodic stabilization is done.
This is done by asking the successor for its predecessor.

When doing a lookup, a client sends a request to its successor, who will forward it until it lands at the node who is responsible for that key.
The node can then respond with the lookup result.
This is not very efficient, so instead chord introduces a finger table which stores a sucessor some keys.
The distance in keys in the table doubles, thus caching more locations for keys nearby.
This makes the search take O(log(n)), because we can in each jump halv the distance to our wanted key.

When joining, a node must know a single node in the ring.
It can then send a join message which will travel the ring until the predecessor and successor.

### Pastry

Pastry works like chord, in that nodes are aranged in a ring, and id's are assigned to nodes.
Each node also holds multiple successsors and predecessors.

It uses prefix matching to figure out where to send to.

Because multiple nodes can match a prefix, we will often start with shorter prefixes, as they are less specific and allows to select a closer node.

### Tapestry

Same routing system as pastry, but gives more **flexibility** because applications can place replicas close to frequent users of a resource.

# Iot and Routing in IoT

WSN or Wireless Sensor Networks, where very popular in 2005.
Kind of what IoT is today.
Usefull for monitoring of ecosystems, disaster and assets.
Good example to use is the dutch flower auction, where it is used to tracker where carts are.

Here the challenge is to connect sensors wirelessly, in a power efficient way.

Communication is with multihopping between WSN, and then have a decide connect this to the internet with GPRS (General Packet Radio Service).
Therefore messages must be very short, only around 42 bytes.
Here messages are timestamped with the local clock of the device, and with the GPRS receive time.
The global time can then be reconstructed on the DB.

Traditional wifi and IP is often too expensive for WSN, instead using protocols like bluetooth between sensors.
The standard 802.15.4 is designed for wireless personal area networks.
The MAC layer had two types of devices, Full function device (FFD) which can talk to any other type and can become a network coordinator, and
Reduced Function Device (RFD) which can only talk to the network coordinator.

CSMA-CA is Carrier Sense Multiple Access Collision Avoidance, where the backoff is used if channel is occupied.

## Zigbee

Is on top of 802.15.4, and provides routing.
Here nodes join a network with a 16bit address, and there are routing algorihms for tree, star and mesh topologies.

## 6LoWPAN

Works like an IPv6 over 802.15.4.
Here the 64bits of the MAC address is reused for the IPv6 address which is 128 bits.

## LoRa

Not based on 802.15.4, but has its own PHY.
Here LoRaWAN is a MAC layer on top.

This gives a long range of around 2-5 km in urban environments, but above 15 in open.

Gateways are used to connect end devices to the internet.

## SigFox

Very long range, up to 40km with directional antennas.
SigFox company takes care of coverage, and charge through subscriptions.

Therefore this is more fitting for applications where there are few and small messages.

## NB-Iot

Or narrow band IOT.

## Routing

We need to take some things into account

  - Delay
  - Link load
  - Router load
  - Energy consumption
  - Loss probability

## Zigbee

Here there is a single coordinator, some routers and some end devices.
And networks can be structured as Star, Tree, or Mesh networks.

Addresses are assigned with a distributed address assignment scheme.
Here the coordinator holds three parameters: max number of children of a router, max number of child routers, depth of network.
These paraters are used by a router to calculate a value `Cskip` which is used compute the size of childrens pool.

In a star network we do not need to route, because everyone is connected via the coordinator.
With a tree we can use the address scheme to follow the correct path.
This can also be done with the mesh, but AODV can also be used.

## Directed Diffusion

Way to find a path from a source to a sink.
Here the sink floods an interest (for example for data in a squeare at a certian update interval).
First this may be exploratory, so at a lower interval.
Along the way a reverse information towards the sink is formed (called *gradient* i think).
These are soft state in that they time out.

Then nodes that can fullfill the interest by sending unicast back.
Here the cache is consulted to route the entry back.

Now the source can change the interval to the wanted value and use the existing gradient.

## Dynamic Source Routing

This is very much like we had in the other course, with the route requests (RREQ).
Remember that there where several problems, the slides mention the one with collisions.

When reached the destination, a RREP is sent back.
Routes back are cached.
Packages sent thereafter then include the whole route the packet must follow.

This also has the problem that packet header grows with network size, because the whole route must be contained.
There can also be alot of replies (*reply storm*) because nodes answer from their cache.

## Adhoc On-Demand Routing (AODR)

Instead of including the route in each packet, we let each node hold a routing table.
Here nodes which are traversed by the route request set up a reverse path pointing to source.

In the route request we include a sequence number.
Then nodes that know a newer path can reply.

Also nodes that return the routing reply can record that path to the destination.
Timeouts are used to invalidate routes.

