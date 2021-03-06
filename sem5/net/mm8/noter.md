# Can
```
2020-10-01:s5/net/mm8/noter/1 #2280
```

Can lever i layer 1 - 3 i OSI modellen.

## Bus

Requires that a single bit is received by all bus members.

1 is recessive, while 0 is dominant.
Recessive is the default so pull up and dominant is when the line is pulled down.

```
0 + 0 = 0
1 + 1 = 1
0 + 1 = 0 # Because 0 is dominant
```

CAN defines 0 as the dominant bit.

## Frame

Node id is also used as priority.
Smaller id gives a higher priority.
It therefore uses `CSMA/CA`.
This can be seen below:

1. First everyone starts transits zero.
2. Then nodes starts transmitting their id.
3. If a node hears something different than they are transmitting they know they are loosing.
4. The winner (TAKES IT ALL) can then send the rest of the frame.
5. Loosing nodes wait for end of frame, so they can try again.

In the ACK field the receiver sends a dominant bit to signal if the frame went fine.

This means that we are constantly listening while receiving and others can also jump in.

### Addressing

ID is not really a address.

One does not operate on source and destination but more different message ID's.
Like different sensor values have different id's, and other nodes can then subscribe on these id's.

Nodes only listen for id's they are interested in.

### Frame types

Data Frame
:   a frame containing data.
Remote frame
:   a request for a specific resource.
Error frame
:   transmitted by a node on a error.
Overload frame
:   Whaat

## Bit synchronization

Nodes need to agree on whats on the bus.

Bit time must be twice propagation time.
This means long lines give slower speeds.

### Problem
Periodic messages with different priority can give non-deteministic behavior, as their clock go in and out of phase.

This can be solved by finding a worst case and checking if it lives up to a requirement.
However this can be hard if there are many messages.

One can also run simulations.
