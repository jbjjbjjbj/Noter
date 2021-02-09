# Noter til probability m2

## Random variables

Her mapper man fra et sample space S til en variabel.
Her kalder man variablen et stort tal R eller sådan noget.

Derfor er et random variabel egentlig en transformation mellem S og real tal.

*X er en descrete random variable hvis dens range er countable.*

For continues random variables the following is true:

$$
P(X = x) = 0
$$

## Functions beskriver ens random variable

### Cumulative Distribution function

Her måler man prob for at ens random er mindre end et bestemt tal.

$$
F(x) = P(X \leq x)
$$

Man kan også finde det for en range:

$$
P(a < X \leq b) = F(b) - F(a)
$$

Ved discrete random variables vil denne være en slags trappe.

Kan sige at den er *continues from the right* eftersom man har $\leq$ i definition.

### Probability Mass Function

Works only for discrete random variables.
Is defines as the probability that $X = a$:

$$
p(a) = P(X = a)
$$

From here CDF can be found:

$$
    F(a) = \sum_{all x \leq a} p(a)
$$



### Probability Density Function

Her finder man P i et evigt lille interval:
Is the derivative of the CDF.

$$
    F(a) = P(X \in (-\infty,a]) = \int_{-\infty}^a f(x) dx \\
    f(a) = \frac{d}{da} F(a)
$$

The following must be true:

$$
    \int_{-\infty}^{\infty} f(x) dx = 1
$$

## Multiple random variables

Have multiple random variables, which can be or is not correlated.
Can define the joined CDF:

$$
    F_{XY}(x,y) = P(X \leq x, Y \leq y)
$$

One can also find the probability of one of the variables. (The *marginal*)

$$
    F_X(x) = P(X \leq x) = P(X \leq, Y < \intfy) = F(x, \infty)
$$

One can not go from marginal to the joined, as they do not contain enough information.
This is only possible if X and Y are **independent**.

$$
    F_XY(x,y) = F_X(x) \cdot F_Y(x) \\
    p(x,y) = p_X(x) \cdot p_Y(y) \\
    f(x,y) = f_X(x) \cdot f_Y(y)
$$

### Joined PMF

$$
    P_{XY}(x,y) = P(X = x, Y = y)
$$

    vim: spell spelllang=da,en

