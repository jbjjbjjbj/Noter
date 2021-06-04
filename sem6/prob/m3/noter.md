# Notes for third probability lecture

*Moment generation function* is a third way to describe the behavior of a random variable.

Can also find *Key performance indicators*.
Which will be explained in this document.

## Expectation

Is just the mean value.

$$
    E[X] = \sum_{i} x_i P(X = x_i) = \sum_{i} x_i p(x_i)
$$

In the continues way integral is used instead.

$$
    E[X] = \int_{\infty}^{\infty} x f(x) \mathrm{dx}
$$

Can also calculate expectation distribution function, however this can only be used if all values are non-negative:

$$
    E[X] = \sum_{k=0}^{\infty} P(X > k) \\
    E[X] = \int_{0}^{\infty} (1 - F(x)) \mathrm{dx}
$$

Tatianas recommendation is to calculate expectation from the PDF.




### LOTUS


### Some properties

$$
E[a X + b] = a E[X] + b
$$

The mean of a constant is the constant itself:

$$
E[b] = b
$$


### Multiple variables

If $Z = g(X,Y)$ one can find the expectation with:

$$
    E[Z] = \sum_{i} \sum_{j} g(x_i, y_j) \cdot p(x_i, y_j)
$$

If continues just use integrals instead.

$$
    E[Z] = \int_{-\infty}^{\infty} \int_{-\infty}^{\infty} g(x, y) \cdot f(x, y) \mathrm{dxdy}
$$

The following rule can be used:

$$
E[X+Y] = E[X] + E[Y]
$$

If $X$ and $Y$ are **independent** the following is true:

\begin{align*}
    E[g_1(X) \cdot g_2(Y)] &= E[g_1(X)] \cdot E[g_2(Y)] \\
    E[X \cdot Y] &= E[X] \cdot E[Y]
\end{align*}

## Variance

Describes the mean of the distance between outcomes and the overall mean.
Good way to describe the spread of the random variable.

\begin{align*}
    Var(X) &= E[(X - E[X])^2] \\
    Var(X) &= E[X^2] - E[X]^2
\end{align*}

If there is no power of two, it will be mean minus mean, which wont work.

One can define the *standard deviation* to bring back the unit from squared.

$$
    Std(X) = \sqrt{ Var(X) }
$$

A rule for variance:

$$
Var(a X + b) = a^2 Var(X)
$$

The variance of a constant is therefore $0$.

### Summing

$$
Var(X+Y) = Var(X) + Var(Y) + 2 Cov(X, Y)
$$

If X and Y are independent the Cov part disappears.

## Covariance

\begin{align*}
    Cov(X,Y) &= E[(X - E[X]) \cdot (Y - E[Y])] \\
    Cov(X,Y) &= E[XY] - E[X] \cdot E[Y]
\end{align*}

Shows whether two variables vary together, can be both positive and negative.
If it is possible $X$ and $Y$ are varying from the average together.

Some rules below:

\begin{align*}
    Cov(X, X) &= Var(X) \\
    Cov(a X, Y) &= a Cov(X, Y) \\
    Cov(X + Y, Z) &= Cov(X, Z) + Cov(Y, Z)
\end{align*}

If X and Y are independent, then covariance is zero (X and Y are *uncorrelated*).
X and Y can be uncorrelated and not be independent.

## Correlation coefficient

It is hard to compare covariance as the value is dependent on the size of X and Y values.
We can therefore take the Correlation coefficient instead.

$$
    Corr(X,Y) = \frac {Cov(X,Y)} {\sqrt{Var(X)} \cdot \sqrt{Var(Y)}}
$$

    vim: spell spelllang=da,en
