# Logic

TODO Manger at lave en summary.

## Opgaver

### 1.

A) Yes, T
B) Yes, T
C) Yes, T
D) Yes, T
E) No
F) No

### UNKNOWN ORIGIN (12.)

A) if you have the flu, you miss the final examination
B) you pass the course if and only if you do not miss the final examination
C) if you miss the final examination, you do not pass the course
D) you have the flu, miss the final examination and pass the couse

### 15. (13.)

A) ¬p
B) p ^ ¬q
C) p -> q
D) ¬p -> ¬q
E) p -> q
F) q ^ ¬p
G) q -> p

### 20. (18.)

A) T
B) T
C) F
D) T

### UNKNOWN ORIGIN(31.)

A)

| p  | ¬p | p  ^ ¬p |
| -- | -- | --      |
| T  | F  | F       |
| F  | T  | F       |

B)

| p  | ¬p | p v ¬p |
| -- | -- | --     |
| T  | F  | T      |
| F  | T  | T      |

C)

| p  | q  | p v ¬q | ( p v ¬q) -> q |
| -- | -- | --     | --             |
| T  | T  | T      | T              |
| T  | F  | T      | F              |
| F  | T  | F      | T              |
| F  | F  | T      | F              |

D)

| p  | q  | ( p v q) -> ( p ^ q ) |
| -- | -- | --                    |
| T  | T  | T -> T = T            |
| T  | F  | T -> F = F            |
| F  | T  | T -> F = F            |
| F  | F  | F -> F = T            |

E)

| p  | q  | (p -> q) | (¬q -> ¬p) | (p -> q) <-> (¬q -> ¬p ) |
| -- | -- | --       | --         | --                       |
| T  | T  | T        | T          | T                        |
| T  | F  | F        | F          | T                        |
| F  | T  | T        | T          | T                        |
| F  | F  | T        | T          | T                        |

F)

| p  | q  | (p -> q) | ( q -> p ) | (p -> q) -> ( q -> p) |
| -- | -- | --       | --         | --                    |
| T  | T  | T        | T          | T                     |
| T  | F  | F        | T          | T                     |
| F  | T  | T        | F          | F                     |
| F  | F  | T        | T          | T                     |


### (40. )

All the paranterees must be true, they can be split up.

r is in two parantesees ( q v ¬r ) and ( r v ¬p ).

If r is true q must also be true for ( q v ¬p ).

Therefore in ( p v ¬p ) p must also be true.

Therefore it creates a kind of circle, that also works then one is false.

### (44. )

A) 

 01011
 11011
v-----
 11011
 11000
^-----
 11000

B)

 01111
 10101
^-----
 00101
 01000
v-----
 01101

C)

 01010
 11011
x-----
 10001
 01000
x-----
 11001

D)

 11011
 01010
v-----
 11011

 10001
 11011
v-----
 11011

 11011
 11011
^-----
 11011


### (7. )

Already done this

### (9. )

The rest is just stupid.

### (20. )

| p  | q  | p x q | p <-> q |
| -- | -- | --    | --      |
| T  | T  | F     | T       |
| T  | F  | T     | F       |
| F  | T  | T     | F       |
| F  | F  | F     | T       |

The two last columns are the negatives of each other thus

p x q = p <-> q



