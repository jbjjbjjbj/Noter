

# Opgave 1

Nope

# Opgave 2

    Show that the following

    R = ~(~(A * ~B) * ~(~A * B))

    is XOR

Man kan skrive exclusive or som:

```
(A + B) * ~(A * B)

(A + B) * (~A + ~B)
A * ~A + A * ~B + B * ~A + B * ~B
A * ~B + B * ~A
~(~(A * ~B) * ~(~A * B))
```

yaay

# Opgave 3

    Reduce the following

Jeg tager bare den først.

```
A * ~B * ~C + A * B * ~C + ~A * ~C

~C * (A * ~B + A * B) + ~A * ~C
~C * A + ~A * ~C
~C
```

# Opgave 4

    Find expression

```
X = ~(A * B)
Y = ~(A * X)
Z = ~(B * X)
C = ~(Y * Z)
D = ~X

C = ~(~(A * ~(A * B)) * ~(B * ~(A * B)))
D = ~~(A * B) = A * B
```

