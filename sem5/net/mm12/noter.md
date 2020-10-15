```
2020-10-15:s5/net/mm12/noter #6be5
```
# Sidste gang
## Konklusion af opgaver fra sidste gang

Fejl i TCP afhænger meget af hvilke pakker der bliver tabt.

## TCP wireless

TCP performance is very affected by wireless errors.
Solutions:

 -  Can use some special ACK which uses bitfields for acking multiple packets.
    Also called *SACK*, i think.

 -  Can Also terminate TCP in the middle and switch over to another protocol.
    Then move back to TCP at the other end of wireless.

 -  Modify layer 2 to work better with TCP.
     -  Can for example check if dupack and then drop it.

FEJL PÅ SLIDES: slide 31 "down-stream" skal være "up-stream".

# Fault tolerance

Dette er noter fra mm12.

How to handle faults in a network of services?

1.  Define a list of possible errors, with likelihood.
    Here errors can be prioritised based on likelihood and impact.

    Also called *Fault analysis*.

## Types of failures

 -  Crash
 -  Timing
 -  Assertive
 -  Arbitrary/Byzantine

## Metrics

**Availability** is the fraction of time the system is available.
For very reliable systems this should be $1-10^5$.

If there is **replication** the availability becomes $1-(1-A)^N$, where N is the
number of servers.

## Replication

> If availability is to low, just throw more servers at it. /s

Have multiple servers.
How to split traffic between servers:

 -  Just give a list of servers

    Means clients must do failover themselves.
    Sometimes this is not desirable.

 -  Have servers on the same ip address.
    So the client is unaware.

    This makes a constraint on the network, which must to load balancing.
    This could be done with a load balancer or with ARP.

 -  Have name servers which update depending on server availability.

TODO: Cluster framework.
