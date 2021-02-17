# Opgaver til prob m2

## Opgave 1

Man kan sige at chances for at en kvinde kommer først er 50%.

$$
P(1) = \frac 1 2
$$

Herefter kræver det at en mand for først og en kvinde får næste.

$$
P(2) = \frac 5 10 \cdot \frac 5 9 \\
P(3) = \frac 5 10 \cdot \frac 4 9 \frac 5 8 \\
P(4) = \frac 5 10 \cdot \frac 4 9 \frac 3 8 \cdot \frac 5 8
$$

osv.

## Opgave 2

### A)

Dette har jeg gjort på papir.

### B)

$$
P\left(X > \frac 1 2\right) = 1 - F\left(\frac 1 2\right) = 1 - \frac 1 4 = \frac 3 4
$$

### C)

$$
P(2 < X \leq 4) = F(4) - F(2) = 1 - \frac {11} {12} = \frac 1 {12}
$$

### D)

$$
P(X < 3) = \frac {11}{12}
$$

### E)

$$
P(X = 1) = \frac 2 3 - \frac 1 2 = \frac 1 6
$$

## Opgave 3

Først skal man finde $\lambda$.

$$
    \int_{0}^{\infty} \lambda e^{- \frac x {100}} \mathrm{dx} = 1 \\
    \left[ - \lambda 100 \cdot e^{- \frac x {100}}\right]_{0}^{\infty} = 1 \\
    \lambda \cdot 100 = 1 \\
    \lambda = \frac 1 {100}
$$

Nu kan man sætte 50 til 150 ind.

$$
    P(50 < x \leq 150) = \int_{50}^{150} f(x) \mathrm{dx} = - e^{- \frac {150} {100}} + e^{ - \frac {50} {100}} = 0.3834
$$

Derefter kan vi tage fra 0 til 100.

$$
    P(x < 100) = \int_{0}^{100} f(x) \mathrm{dx} = - e^{- \frac {100} {100}} = - \frac 1 e
$$

