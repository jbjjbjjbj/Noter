# Topic 1 Time order

## Distributed system

N nodes working together on a overall task.
Interacting via communication network.

Challenges include.

- Bad communication channel
- Global state is hard
- Local clocks may not be in sync
- Ordering of subtasks
- Handling faults or malicous behavior

Ways to implement ordering.

- Clock synchronisation
- Use of logical clocks
- Algorithms that do not rely on order of events

## Time and clocks

Monotonicity
:   Når et ur ikke kan gå tilbage i tiden. Altså hvis `t1 > t2`, så er t1 senere end t2.

Local clocks have drift.
To make them usefull, they must have bounded precision and accuracy.

## Notions of time

- UTC
- Internal clocks
    Often implemented with a counter function, which counts at a given frequency.
- "Time-stamping"
    Event ordering

## Clock synchronization

Uses measured round trip time to calculate the delay of the received time.

Clients can either pull a server, or the other way around.

### NTP

Clients can pull times from another server.
Builds a tree of servers.

Represents time using number of seconds since 1900-01-01.
Timestamps all messages, and timestamps of recent events.

Accuracy is ~1ms for LAN and ~tens of ms for Internet.

## Ordering

Total order is if for all times `a` and `b`: `a > b or b > a`.
So all times can be compared.

Transisive relation
:   If `a, b` can `b, c` can be compared then `a, c` can too.

Irreflexive
:   That `a, b` cannot be compared.

If precise physical clocks are posible, total order can be achieved.

Partial order implies that concurrent events can occur.

## Partial order

Important to be able to say a happened before b, as a could affect the result of b.

Consistent clock
:   If a happened after b then `C(a) < C(b)`. Where C translates event to time. *Strictly consistent* if the reverse is also true.

Local logical clocks can do this internally in precesses and between processes.

Causal order
:   Her kigger man på om et event A kan have forårsaget B.

## Scalar logical clocks

Have a counter which is incremented before each event.
Include this counter in each message sent.

When a recipeint receives a message set its counter to either its own or the senders depending on which is largest.

Scaler clocks are not strictly consistent, but can be used to define total order.

### Vector based

Each node keeps a vector of the logical clocks of all other nodes.

# Topic 2 Algorithms and Consistency

## Mutex locking

Different solutions.

Simple: A node can request a lock by sending a request, and locking nodes can object.
Requires:

- FIFO: message order between processes is preserved
- Every messages is received
- Each process can communicate with all other

## Leader election

Contralized control is useful in some algorithms.
If done distributedly all nodes must be able to take this role.

Requires a algorithm to elect leader.
Can be done with mutex locking, but better methods exist.

Nodes broadcast their role id(random) at a random time.
If a node hasn't received at higher id, it broadcasts its own.

## Transaction and consistency

Transaction properties:

- Atomicity (result is either commit og abort, not a half failure state)
- Durability (persistent results)
- Isolation (current transactions do not influence other transactions)
- Consistency (transactions go from a consistent state to another)

Global state cut
:   Taking a snapshot of consistent state, not including transactions.

Different cuts/snapshots.

- Strongly consistent: No messages in transit
- Consistent cut: Messages in transit not included
- Inconsistent cut: Messages in transit are included

## Computational model

Includes read and write, FIFO queues, stacks etc.

Can be implemented as:

- Central storage
- Master storage and copies
- Fully symmetric distributed storage

Consistency criteria
:   correctness of result of distributed sequence of operations.

### Linearizability

A sequence of events are linearizable consistent if:

- If a sequential order can give same result
- This sequential order is consistent with the real order of events

Requires global time, and limits concurrentcy.

### Serializability

- If the sequential order is consistent with the real order of operations on each node.

# Topic 3 OSI

Layered protocol to ease implementation of layers and adding new layers.
As layers only talks to the layers above and under.

1. Physical layer:
    Defines physical things like voltage, frequency etc.
    Different services which next layer relies on.
2. Data link layer:
    Breaks data from physical layer into packets, and handling error at the physical link.
    Includes ethernet.
3. Network layer:
    Handles routing of packets across the network.
    Where things go from single hop to many hops.
    Implements the Internet with IP addresses.
4. Transport layer:
    Handles end to end connections, where ports live.
    Where connections are implemented, such as in TCP.
5. Session layer:
    Handles session :-).
    Things like *authorization* and *authentication*.
6. Presentation layer:
    Formatting of data, such as MIME, ASCII or PGP.
7. Application layer:
    Applications such as web browsers, ssh or email.

## Connection oriented

Simple communication can just send a packet with a destination on it.
If the packet is lost it is just lost.

A connection can be setup, packets can be sent and it cna be torn down.
This allows for re-transmission and re-ordering of packets.

# Topic 5 Mac and link layer

Started with telephone switching where two are connected using a continues connection.
When computers came packet switching was created for internet packets.

These where combined when packet switching became fast enough.

## Link layer

Often comes in short burst

Use *error correction* when retransmission or feedback channel is not available.

### ARQ

ARQ (Automatic Repeat Request) handles errors and retransmission.

Uses different retransmission strategies:

- Stop and wait: 
    Vent på ACK før den næste packet skal sendes.
- Go back N: 
    Sender will keep a window of sent windows and will keep track of which sequence number has been received.
    It will go back if missing.
- Selective repeat/selective reject: 
    Receiver selectively says which frames are missing.

#### Hybrid ARQ

Combination of error control schemes.

Type-1
:   Error detection and correction.

Type-2
:   On a good channel use pure ARQ, if not add more parity bits.

## MAC

Multiaccess media instead of point to point.
Requires Media Access Control sublayer.

Different way to have multiple devices talk on one line.

### Static allocation

Devide channel in portions and allocate these to devices.
This can be done in different ways:

- SDMA (space devision):
    Segment using space, as with different directed antennas or wires.
- TDMA (time devision):
    Have devices transmission time slots.
- FDMA (Frequency devision):

Static allocation can be good with a small number of devices.
But not to good if many devices or bursty traffic.

#### Frequency hopping

Combination of FDMA and TDMA.
Can be done with fast hopping (for every symbol) or slow hopping (for every message).

Can withstand interference, as multiple frequencies are used.

Synchronization and discovery can be a challenge.

This can be done by first sending a seed and offset.
And then a new clock reference is sent with every packet.

This requires that slaves can't got to sleep for too long.

### Dynamic schemes

#### Random schemes

Direct transmission without contention phase, so collision are very possible.
Suitable for short messages, which can afford to be retransmitted.

##### Aloha

Transmit immediadly, incase of collision retransmit after random time.

Special case of stop and wait.

**Slotted aloha** created slots where transmission is allowed.
Not as many collisions, as only start can go wrong.

##### CSMA

Listen before talk, as listening is not super demanding.
Does not relieve of collisions, because sending takes time.

1-persistent
:   Send if the channel is idle.

Non-persistent
:   Send if idle, if idle send. If not idle then wait for random period of time.

Can deploy collision detection to stop the transmission if a collision happens.

*Consensus reenforcement* what?

#### Slotted systems

Assign allowed transmission times to slots.

Can use base station as reference, but distributed is much harder.

#### Reservation schemes

Devices signal they want to sent in a contention phase.
The winning device will get to send a message collision free.

Nice for long messages.

#### Collision detection in radio

Harder as with wire, as the signal is weaker throughout the range.
Often not implemented in wireless systems.

ACK is often required.

#### Wireless problems

*Hidden terminal* is when a collision happend between two temrinals which can't see each other.

*Exposed terminal* is when a station can't transmit because the channel looks busy, but really transmission is possible.

#### MACA

Uses signalling packets for collision avoidance.
Terminal sends RTS (Request) and receiver can answer with CTS if the channel is ready.

Avoid hidden terminal, but not exposed terminal.
As requests will collide at B.

# Topic 6 WLAN

Architecture in networks:

- Station (STA):
    Terminal with radio which communicates with access point.
- Basic Service Set (BSS):
    Group of stations using the access point
- Access point:
- Portal:
    Bridge to other wires network
- Distribution system:
    Interconnected network to form one logical network.

*Adhoc* network are only between stations directly.
Important word is IBSS (Independend Basic Service Set), which is a group of stations using the same frequency.

*Direct communication* is when a station functions as a access point.

TODO der står en del om PCF i slides.

## MAC

Two different schemes:

- Distributed Coordination Function (DCF):
    Implementation of adhoc networks and all users contend to accessing the channel.
- Point Coordination Function (PCF):
    Is based on polling, performed by a AP.

These want to achieve two *traffic services*.

- Asynchronous Data Service (mandatory):
    - Support for multicast and broadcast.
    - Priority networks.
- Time bounded service (optional)
    - Implemented using PCF.

## Carrier sensing

Can be done in two different ways.

- Physical carrier sensing:
    Detects activity on the channel via signal strength.
- Virtual carrier sensing:
    Detects from received header information, where packets say how long they utilize the channel.

The channel is marked busy if one of them indicate a busy channel.

## NAV

Network Allocation Vector is used by stations to predict the duration of the current transmission.

## Performance

Theoretical throughput calculates throughput deterministic analysis.
Does not take collisions and channel errors into consideration.

Multihopping in networks can give problems as it blocks many connections.

TCP also gives poorer performance as it quickly breaks.

A good solution would be multi-radio per station so forwarding can be done on another channel.

## Transmission range

Limited by 3 different things.

- Transmission range:
    Limited by the transmission power and radio propagation.
- Physical carrier sensing range:
    Is the range where another station.
    This is larget than the transmission range.
- Interference range:
    Range which the transmission will cause interferenence on a receiver.

## Access methods

- DFWMAC-DCF CSMA/CA (mandatory):
    - Collision avoidance with back-off mechanism.
    - Using ACK for non broadcast packages.
- DFWMAC-DCF w/ RTS/CTS (optional)
- DFWMAC-PCF (optional):
    Access point polls terminals according to a list.

    Pull data in a superframe, which is started with a beacon from AP.

# Topic 7 Bluetooth

Bluetooth uses frequency hopping.


Alternates RX and TX meaning master always transmit on odd time slots, and a slave transmit on even time slots.
A slave can therefore not initilize a conversation itself.

## Discovery

Complex in bluetooth classic and takes some time.

Bluetooth low energy has 3 advertisement channels where devices discover each other.

## Different link types

- Synchronous Connection Oriented for voice:
    - Circuit switched with preallocated bandwidth.
    - No retransmission
    - Symmetric
- Asynchronous Connection Less for data:
    - Variable time slots
    - Uses ARQ protocol
    - Symmetric
- eSCO for streaming:
    - Retransmissions immediately after received slot.
    - Symmetric or asymmetric

Symmetric means that RX packets are the same type as TX.

## Errors

Can use different error correction schemes:

- 1/3 FEC where each bit is 3 times.
    Uses majority voting.
- 2/3 FEC uses math to encode 10 bit code to 15 bit code. So 1 parity per 2 bits.

But can also use ARQ schemes.

## Energy states

Active
:   Channel is active and slave and master are kept in sync.

Sniff
:   Slave only listens for synchronization beacons at specific times, this entering low power mode.

Hold
:   Can be used if other actions must be performed such as participating in other networks.
:   Here it will only listen for specific messages.

Park
:   Master parks slaves to support many devices is piconets.

## Interference

Bluetooth utilizes AFH (Adaptive frequency hopping) where is tries to avoid frequencies where many collision happen.

# Topic 8 CAN

Why use a fieldbus instead of dedicated wires:

- Cost savings
- Reduction of weight
- Reliability
- Easier fault diagnosis
- Redundancy

Fieldbusses often implement multiple OSI layers, and the layers 3 to 6 are non existent.

## CAN

CAN is good for noisy environments.

CAN uses an single set of wires where everything is broadcast transmissions.

Synchronization is required and resyncrhonization is done by looking at edges of signal.
Because of this, long silent sequences should be avoided.
This is done with bit shuffling of bits.

Requires the idea of *dominant bits* which are explained in the question section together with addressing and priority.

### Messages types

- Data frame: a frame containing node data
- Remote frame: a request for a specific ID
- Error frame: transmitted by a node on error
- Overload frame: used to create a delay if more time is needed

# Topic 9 Network layer

## Routing

Different kinds of routering

Source routing
:   First router decides the whole route.

Hop-by-hop routing
:   Each router only decides what the next hop should be.

### Algorithms

How to route a large network which can change dynamically.

- Distance Vector routing:

    Keep a vector of all other nodes in the network, including a distance and next neighbour.
    This has the advantage of little overhead, but has slow convergence and count to infinity problem.

- Link state routing

    Keep a graph of the whole network and use dijkstra to find shortest route.
    However this comes at the cost of scalability.

- Hierarchical routing

    Much better for large network where one only stores information about a specific region and does not keep track of every route.
    Much like the postal system.

## Congestion

When the traffic exceeds the limits of the network or a part of it.
It is desirable if hitting this limit does not congest the network.

To prevent congestion one should monitor the network.
Here are some things to avoid:

- Avoid oscillations
- Avoid increasing traffic to much

Congestion is affected by many things from the different layers.
These are summarized on slide 18.

### Solutions

Sending of *choke packages* if a node gets congested.
This is sent as a notification from receiver to sender.

With *Explicit Congestion Notification* a node can set a congestion bit on a passing packet.
When a reply is sent back this bit is included and a sender will know that congestion happen on a specific route.
This has a slower reaction time.

### Quality of service

Different services may have requirements to the network.
These requirements could be on Bandwidth, latency, jitter or loss.

For example video services require high bandwidth and predictable latency(low jitter).

Telephony does not require a lot of bandwidth and lost packages are okay.
However it requires low latency and jitter to make a conversation doable.

Slide 25 summarizes different requirements for different services.

#### Queuing

One can use a simple FIFO queue which gives no QOS, as who comes first get served first.

Weight Fair Queuing (WFQ) select packets based on a priority scheme, so important packages will get served first.

WFQ also enables ISP's to prioritise enterprise traffic over commercial ones.

#### Shaping slow

Ways of affecting jitter and latency can be done with special queues.

If we want to output traffic predictably with a limited bandwidth one can use a *leaky bucket*.

##### Leaky bucket

Make a irregular slow of packets into a regular one.

Leaks out packets at a constant rate.

Defined by its output rate and capacity.

##### Token bucket

Contains memory and allows for creating bursty traffic.

Traffic is controlled by tokens.
When tokens are available packets are sent.
A number of tokens are added at a constant rate.

Defined by the rate of tokens and the max amount of tokens.

Can be combined with a leaky bucket to limit the bursty traffic.

## Ip address classes

- Class A: 1.0.0.1 to 126.255.255.254
- Class B: 128.1.0.1 to 192.255.255.254
- Class C: 192.0.1.1 to 223.255.254.254
- Class D: 224.0.0.0 to 239.255.255.255
    - Used for multicast
- Class E: 240.0.0.0 to 254.255.255.254
    - Reserved for future use and research.

This has the disadvantage of wasting a lot of space.

## Ip routing

Operators have AS numbers with each AS number assigned to a area.
Between AS numbers OSPF (Open Shortest Path First) is used.

AS numbers communicate routes using BGP.

# Spørgsmål

If we answer a question nicely and quickly, we just get another question.
We should not work hard to scretch time.

## Time, synchronization and order

1. **Explain the need for clock synchronisation by giving an example scenario. Provide an example synchronisation approach for 2 nodes and discuss its advantages/disadvantages**

**Ide 1:**

A distributed chat system requires must be able to preserve order of messages and their received times.
Conversations often have questions which other can answer, which can be confusing if the order is skrewed up.

It is also important for users to see when messages where sent.

1. Alice sends a message to Bob.
2. Bob will respond with a ACK.
3. Alice sends the measured round-time to Bob.
4. Bob sends the measured round-time to Alice.
5. Alice and Bob independedly calculate the average delay between the two round times.
6. The one behind sets it's clock to the most forward one.

The has the advantage that it works without a central time server, however comes with many problems.

- Alice and Bobs clocks will quickly come out of sync with the rest of world, making the timestamps useless for users.
- This requires alot of extra traffic

**Ide 2:**

Many websites often have authenticated user interaction, where users log in to a session.
This is often implemented with a server recording sessions and their expire time.

If this is to be done distributed between multiple server, all servers must have 

2. **Explain the concept of causal partial order using an example event diagram.**

Svaret i notesbog.

3. **Explain the motivation and realization of a logical clock using an example.**

Multiple users add and remove text to a distributed document sharing program.

When a users adds text it sends only the addition and where it happened to other clients.
It is therefore important which order changes arive in as they depend of the previous state of the document.

However it does not matter which time edits happen on so a real clock is not needed.
Therefore a logical clock can be used to insure additions are applied in the right order.

Shown in notebook.

4. **Explain vector clocks and scalar logical clocks using an example and discuss their differences**

Scalar clocks are implemented as a simple counter, counting up for each action.
On receiving a message which a clock value a client takes the biggest.

If two events have et same scalar clock value, its not possible to determine their order.
Scalar clocks have eventual consistent time.

Vector clocks have a counter for each node, which gives more insight into the order of messages.
This has the advantage that one can see if one event caused another as it is causaly consistent.

Se sammenligning notesbog.

## Distributed exclusion, consistency

5. **Explain the'distributed mutual exclusion' problem and compare it to a centralized approach.**

When sharing resources like memory or devices between multiple nodes, it is often unwanted to have multiple nodes access it.
For example if multiple nodes want to add 3 to a shared variable.

Adding often consist of multiple operations:

1. Retrieve
2. Add locally
3. Store

This is an issue with multiple nodes wanting to add 3.
Mutual exclusion is therefore needed, where a node locks the resource while operating on it.

A centralized method is by having a locking variable which can be read and set atomicly, facilitated by an operating system.
However this is not possible in a distributed system, as a centralized lock server is unwanted.

Instead notes broadcast a lock request, which all other nodes must grant.
A node can then only get the lock if all other nodes permit it.

This comes at a much larger performance cost as the centralized approach.

TODO here a contralized approach may refer to in distributed systems.

6. **Give an example of a distributed read and write operation sequence and explain two different consistency criteria.**

The example can be seen in notebook.

Linearizability, order of events must be preversed on all nodes.
So the example is not linearizable as no valid order can be found.

`r_1` must read a `d` before `r_2` can an `a`, meaning `w_1` must happen after `r_1` which is not allowed.

With sequantial order, time order at each node must be preserved (`w_1` must happen before `r_2`).
So a valid order is.

`w_1(a), r_2(a), w_2(d), r_1(d), w_3(e), r_3(e)`.

## OSI model

7. **What are the advantages of a layered architecture? Explain functionalities of different layers of OSI model.**

Se det der er skrevet oppe i noterne.

## Techniques used at Data Link Layer: ARQ and MAC concepts

8. **Explain the three types of ARQ protocols.**

Stop and wait is when the next packet can't be sent without a ACK from the previus.

Go back N will implement a window of packets available to be sent, and will keep track of the latest ACKED packet.

This allows for the receiver to sent multiple packets thus utilizing bandwidth.

In selective repeat the sender will send many packets and will check which are received. When it will only retransmit the ones that where not ACKED.

9. **Explain the difference between error correction and error detection. Give examples when it is preferable to use one or another, or a combination of them.**

Error correction is when parity data is used to correct errors.
This requires alot of extra parity data, used to reconstruct the original signal.

Error detection is when terminals check for error but cant fix them.
This is often done with CRC, and then not sending an ACK if a invalid packet was sent.

Error detection can be done with much smaller overhead, but requires to a channel to send NACK or ACK.

If this is not available error detection is a bit useless as a retransmission cant be signalled.

Therefore error correction is better.
Error correction is also better for channels with high latency as retransmission are expensive.

10. **Give examples of MAC protocols with static channel allocation. Discuss their advantages anddisadvantages.**

TODO

Focus on FDMA and TDMA.
Obvius advantage is that every thing is nice static and periodic.

If dynamic requires a central entity which makes allocations.

11. **Explain the principle behind a Random Access class of MAC protocols. Give an example of a such a protocol.**
TODO 
12. **Explain main features of Carrier Sense Multiple Access (CSMA) protocol, including the differencebetween non-persistent and 1-persistent versions.**
TODO

## WLAN IEEE 802.11 standard

13. **Explain the Random backoff time mechanism used in the standard. Explain how prioritizationof different messages is realized.**

If the medium is busy multiple devices can wait to send efter.
A random backoff period is introduced to break this summetry.

This is also called a *contention window* where devices fight to be able to send.
Each devices chooses a random count number and counts down.
The first one to reach 0 can start sending.

Priority is implemented with the delay from end busy time to backoff window.
Devices with a smaller delay will have an advantage in the contention window.

The delays are as follows in order of smallest first:

- SIFS (Short Inter Frame Spacing): for high priority such as ACK, CTS or polling responses.
- PIFS (PCF IFS): For timebounded services implemented in PCF.
- DIFS: Lowest priority, for asynchronous data.

14. **Explainthe “handshaking” mode of operation (with RTS/CTS messages) and basic mode (without RTS/ CTS) and the associated trade-offs.**

Handshake done before sending between A and B.

A sends a request (RTS) to send to B, and B will respond (CTS) as soon as it is ready to receive.

This enables other stations close to A or B to see that something is going to happen.
This also solves the hidden terminal problem.

However comes at a bandwidth reduction, and does not work well with multicast and broadcast.

Good to use with large frames or when collisions are likely.

## Bluetooth

15. **Explain the principle of frequency hopping as well as its advantages and challenges in terms of channel sharing and coordination.**

Frequency hopping is the combination of TDMA and FDMA.
It has the timeslots of TDMA, but with each new time slot a new frequency is chosen.

These frequencies are chosen a random meaning different networks can communicate in the same frequency range if they use a different random seed or offset.

Frequency hopping has the advantage of being very resilient to interference, and the timeslots give it predictable behavior.

However initial configuration is challenging as all nodes must agree on a clock offset and seed.
Also clocks must be kept up to date as drifting can cause nodes to get out of sync.

16. **Explain what is a piconet and how data is exchanged between a master and slaves (polling; time synchronization; slot structure; packet types).**

Piconet is a small bluetooth network which allows multiple slaves to connect to the same master device.
Each piconet may contain up to 7 simultaneous nodes, and many more parked slaves.

The master controls all communication in the piconet, so no slave-to-slave communication is possible.
Communication is done using polling where the master will poll a slave with a null packet and it can answer with data.

Polling happens in time TDD (time division duplex) with 625 us size slots.
Time slots are in the range 0 to 227-1, so each node does the same frequency hopping.

Master sends at odd time slots and slaves at even, and because all traffic is controlled by master contention between nodes is avoided.

Packet types:

- ID packet
- NULL, so only contains access code+header
- POLL: used by master to force a response from a slave
- FHS: Used for synchronization to exchange clock and ID information
- DM1: Can carry payload

## Field busses - CAN bus

17. **Explain the role of the frame ID in the priority arbitration scheme used in CAN. Explain what is a dominant and a recessive bit. Show an example of bit sequencesof two frames with different IDs that are transmitted at the same time.**

Many devices can share a single CAN bus, and priority is therefore beneficial.

In a CAN bus each message is sent with a frame ID, which also functions as a priority.

For example all messages belonging to brakes can have a low ID=2 (low is higher priority) while speedometer can have a higher ID=20.

Other nodes can then listen in on a specific message ID they are interested.

This is implemented with the idea of a *dominant bit*, where a line has a default state (recessive) until someone actively does something.
So if one devices writes OFF and another writes ON the dominant bit decides what is read on the line.

When a nodes wants to transmit a frame it will start by transmitting the frame ID.
Other devices can then chime in with their own ID.
If a node measures that its write dominated by another node it will stop.
Nodes with lower ID will therefore win over ones with higher ID.

```
FRAME 23: 00000010111
FRAME 3 : 00000000011
```

Here frame id=3 will win.

## Network layer and routing

18. **You regulate a flow of packets using a token bucket, feeding into a leaky bucket.**
    Assume that the token bucket has a rate of 5 packets per second, and a capacity of 60 tokens.
    The leaky bucket has a rate of 20 packets per second. Assume that the token bucket isempty.
    200 packets has arrived. How long will it take before all packets have left?

First 60 packets are let through to the leaky bucket.
After these the rest (140) will be let through at a rate of 5 packets per second, taking 28 seconds.

Notation will be `input(before,after_input)output`.

```
SEC		TOK				LEAK
1		200(0,200)60	60(0,60)20
2		0(140)5			5(40,45)20
3		0(135)5			5(25,30)20
4		0(130)5			5(10,15)15
5		0(125)5			5(0,5)5
```

It takes 4 seconds for the first 60 to pass through, and after that it goes at the rate of 5 a second.
After 4 it will therefore take 26 seconds to empty the token bucket.

Thus a total of 30 seconds.

SHIIIT token bucker er tom.
**ATTEMPT 2**

Det tager 40 sec for token bucket at give alle pakkerne ud ved 5 per sec.
Efter 40 sec har leaky bucket 5 tilbage, og det vil tage `5/20` sec.

19. **Explain flooding and broadcast storm problem in ad hoc networks.**
20. **Explain the difference between proactive and reactive routing approaches.**
21. **Explain the main principles of Dynamic Source Routing protocol.**

## Transport layer

22. **Explain how TCP achieves reliable in-order delivery of TCP segments. What is the role of a receiver buffer and how is receiver buffer overflow prevented?**
23. **Explain the congestion control mechanismof TCP (slow-start phase and congestion avoidance).**
24. **What are the possible problems of executing TCP over a wireless technology? How can these be mitigated?**

## Introduction to Fault Tolerance

25. **A server node shows has a down-time of 20 hours per year. Show how to calculate the resulting availability Pr(Server operational). **
    Extend your derivation to the case of aredundant structure of 3 servers. 
    Show how to calculate its availability assuming independent faults.


26. **Discuss advantages and disadvantages of cluster structures (that hide the redundancy to accessing nodes) as opposed to an architecture where failover is done via the Clients (such as RSerPool)**
