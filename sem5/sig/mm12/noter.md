# Signal behandling mm12

hej med dig

HUSK: Mærkelig måde at skrive modulo på:

$$
(n \mathrm{modulo} N) = ((n))_N
$$


## Periodisk foldning

Foldning af to periodiske signaler.
Dette kan gøres som en multiplication i frekvens.

Husk at man kun behøver at folde mellem 0 og N, hvor N er perioden af de to signaler.

$$\tilde{x}_3 [n] = \sum_{n=0}^{N-1} \tilde{x}_1 [m] \tilde{x}_2 [n-m]$$

Her er det vigtigt at se at $\tilde{x}_3$ også er periodisk.

## Cirkulærs skifte

Hvis man har en endelig sekvens som man vil rykke, kan man lave et **Cirkulært skift** hvor man tager dem i starten og sætter i enden eller omvendt.

Når man gør dette tager man $x_1$ og $x_2$ og laver periodiske og derefter laver shift.
