# Adhoc routing

Mobility or MANET requires other routing.

## Versus wired routing

Assymetric links
:   Becuase of interference and different power levels, A might be able to send to B
    but not the other way around.

## Routing types

Proactive
:   Routes are known before send, using tables. 
    But does not respond to network changed very vell.
    Also requires lot of traffic to keep up to date.
Reactive
:   Routes are found on demand, so reduces overhead.
    Delay because route must be found first.
Hybrid
:   Something in between.
    Best of two worlds.

## Flooding

Every message is sent to everyone.
Often used for control messages, but not for data as it requires alot of resources.

Nice if nothing is known about network.

**Not always reliable** can have hidden terminal in wifi situration
(also called *Broadcast Storm Problem*).
Can be solved by introducing random small delay when forwarding.

Other solution could be to not forward if already seen *n* times.

## Dynamic source routing

1. **Route discovery**
Using route request (RREQ) to find a route, often with flooding.
2. **Sending data**
3. **Route maintanance**
Keeping the route up to date. This could be done continuesly or when sending new
data.

A reply to RREQ (RREPLY) can then be returned in the route collected with the RREQ.
However if nodes are unidirectional it must be sent back using flooding.

**A problem** with this is the overhead of having the whole route in the packet.

### Route caching

Each node can cache routes to other nodes.
But how to check if a route is broken?

Nodes can check if neighbour connections are broken using MAC ACK.
This node can then signal to sender that the route is broken.

If L2 does not have ACK, we can use control packages.
