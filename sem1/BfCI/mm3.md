# Lektier

## Steps til strong induction bevis

1. *[Basis step]* start med at bevis at P(1) er sandt. Altså hvad resten vil bygge på.
2. *[Inductive step]* bevis at hvis de første P(1 til k) er sandt er P(k+1) også sandt.

## Recursive function

En funktion der regner factorial. 
Altså f(x) = 1 * 2 * 3 * .. * x

Her vil f(1) = 1.
Og resten vil være f(x) = x * f(x-1).

f(1) = 1
f(2) = 2 * f(1) = 2 * 1 = 2
f(3) = 3 * f(2) = 3 * 2 = 6
f(4) = 4 * f(3) = 4 * 6 = 16
