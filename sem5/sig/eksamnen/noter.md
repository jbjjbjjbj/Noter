# TODO 

- [ ] Check opgaver i TOPIC 1
- [ ] Check opgaver i TOPIC 2
- [ ] Check opgave 7 i TOPIC 3

- [ ] Check opgaver i 10
- [ ] Check opgaver i 11

- [ ] Kig på B.1 i reexam

# Topic 1

## Eksponential sekvens

Kan beskrives som:

$$x[n] = A \alpha^n$$

## Komplex eksponential sekvens

(Se slide 42)

Her lader man de to dele (imag og real) være exponentialt vægtede siusiods.

## Frekvens i deskrete signaler

Hvis man har en frekvens $\omega_0$ kan man ikke se forskel fra frekvensen $\omega_0 + 2 \pi$.

## Perioditet

Hvis man har en complex exponential sekvens er det ikke sikkert at den er periodisk.
Her kræver det er at:

$$
e^{j \omega_0 (n + N)} = e^{j \omega_0 n}
$$

Ved sinusiod gælder.

$$
\omega_0 N = 2 \pi k
$$

# Topic 2

## Mærkelige ord

Tids-invariante system
:   Ved en given input-sekvens giver systemet altid det samme output uafhængigt at tidspunktet.

Kausalitet
:   Et kausalt systems output afhænger kun af tidsligere input og ikke fremtidigt input.

BIBO stabilt
:   Et bounded input skal også give et bounded output.

## Lineære tidsinvariante systemer og foldning

Her kan man beskrive systemet som at være afhængig af et input sekvens og et impuls respons $h[n]$.

$$
y[n] = \sum_{k=-\infty}^{\infty} x[k] h[n-k]
$$

Dette kaldes også en *foldning* eller *convolution*.

Foldning er både kommulatativ og distributiv (se slide 17).

### Stabilitet

Et LTI system er stabilt hvis dens impulsrespons er summerbar.

$$
S = \sum_{k=-\infty}^{\infty} |h[k]| < \infty
$$

Dette kaldes også et finite impulse response eller FIR.

Man kan også have stabile systemer med et uendeligt impuls respons, sålænge summen konvergere.
Dette kaldes et infinite impulse response eller IIR.

# Topic 3

## Overførings funktion eller transfer function

Kaldes H og er laplace(eller z) af impuls respons.

$$
y(t) \ast h(t) \leftrightarrow Y(s) = H(s) \cdot X(s)
$$

I frequency domain bliver en foldning til en multiplication og omvendt.

## Z Transform

$$
X(z) = \sum_{n=-\infty}^{\infty} x[n] z^{-n}
$$

Bilateral
:   Two sided, altså fra $-\infty$ til $\infty$.
Unilateral
:   Her har man kun en positive side af summen.

### Konvergens

Vi ved ikke om alle x[n] sekvenser eller z får z tranformation til at konvergere.

Derfor defineres ROC eller Region of Convergense som siger hvilke værdier får transformationen til at konvergere.
Vi kan sige at den konvegere hvis:

$$
\sum_{n=-\infty}^{\infty} | x[n] r^{-n} | < \infty
$$

Fordi konvergens ikke afhænger af frekvens(hvor langt rundt i cirklen man er) men kun $|z|$, må ROC altså være en ring.
Hvis ROC indeholder enhedscirklen $|z| = 1$ betyder det at fourier transformen også konvergere.

### Stabilt

Ens transfer funktion skal indeholde ROC for at være stabilt.

## Fourier transform af sequence

$$
X(e^{j \omega}) = \sum_{n=-\infty}^{\infty} x[n] e^{-j \omega n}
$$

Dette er bare en z transform hvor $z = e^{j \omega}$.

Her er en z tranformation på enhedscirklen i det komplekse plan lig med fourier transform.
Læs mere på slide 14.

## Brug af z transform

En z transform fortæller meget hvis man kan skrive den op som en rational function (altså kan beskrives som to polynomier over hinnanden).

$$
X(z) = \frac{P(z)}{Q(z)}
$$

Her beskriver rødderne i $P(z)$ nulpunkterne i X(z).
Mens rødderne i $Q(z)$ beskriver rødder.

Disse to typer punkter beskriver egenskaberne af X(z).

### Properties

1. ROC er en ring eller disk i z planet
2. Fourier transformen af $x[n]$ konvergere hvis og kun hvis ROC indeholder enhedscirklen.
3. ROC indeholder ikke nogle poler
4. Hvis x[n] kun indeholder elementer i et finite interval, vil ROC indeholde hele z planet undtaget $z = 0$ eller $z = \infty$.
5. Hvis x[n] er en *right-sided sequence*, altså en sekvens der er nul mindre end en bestemt $N_1$, vil ROC gå fra den største pol til $\infty$.
6. Hvis x[n] er en *left-sided sequence*, altså en sekvens der er nul større end en bestemt $N_2$, vil ROC gå fra center til den mindste pol.
7. Hvis x[n] er en *two-sided sequence* vil ROC være en disk.
8. ROC skal være en forbundet region.



# Topic 5

## Frekvens og fase response

$H(j\Omega) kan deles op i frekvens og fase respons:

Amplitude respons: $|H(j\Omega)|$

Fase respons: $Arg(H(j\Omega))$

Amplitude responsen skrives tit i decibel, hvilken regnes ud med:

$$
20 \cdot log_{10} |H(j \Omega)| \qquad \textrm{[dB]}
$$

# Topic 6

## Forskellige typer filtre

Low-pass
:   Lukker af for signalet efter en cutoff frequency

High-pass
:   Åbner for signalet efter en bestemt cutoff frequency

Bandpass
:   Lader en et bestemt interval af signaler igennem

Notch
:   Omvendt af bandpass

Disse kan findes på slide 14

## Forskellige områder i et filter

Passband
:   De frekvenser som filteret skal lade komme igennem, stopper ved $\Omega_p$

Transition
:   Hvor filtreret går fra åbent til lukker, stopper ved $\Omega_s$

Stopband
:   De frevenser som filteret ikke lader komme igennem

# Topic 7

Forklarer en masse om hvordan man laver et IIR filter ud fra en analog specifikation.

Samt bilinear transformation.

## Butterworth

Et idealt filter er ikke muligt, men en approx er butterworth LP filter.

$$
|H_c (j \Omega)|^2 = \frac{1}{1 + \left(\frac{j\Omega}{j\Omega_c} \right)^2N}
$$

Her er $N$ filter orderen hvor højere approx, altså mindre transition band.

## Bilinear 

Her mapper man en frekvens i s domainet til en revolution på enheds cirklen i z domainet.

$$
s = \frac{2}{T_d} \left(\frac{ 1 - z^{-1}}{1 + z^{-1}}\right)
$$

# Topic 8

## FIR filter

Finite impuls response.

Giver mulighed for *Linear phase*, hvilket har den fordel at det er let at manipulere signalet.
Dette betyder at ligemeget frekvensen vil filteret give det samme delay.

Linear phase kan opnås ved at man lader sit impulse response være symmetrisk.

Findes mange forskellige typer beskrevet på slide 17.

Design process er beskrevet super godt i Topic 9 starten af slides.

# Topic 9

Bruger frekvens transformation til at lave LP om til andre.
Se side 553.

# Topic 10

## Quantitation

Fejl der opstår når man convertere noget til digitalt hvor der kun er en fixed mængde precision.

### Time quantitation

Ved Sample hold og man fjerner continues time.

### Variable contituation

I ADC hvor man convetere et signal til en digital værdi på et begrænset antal bits.

Her kommer der noget ind om signal to noise. Se slide 4.

### Computer H(z)

Dette sker ved interne beregninger, da man hele tiden mister precision.

Her er der en masse ting man kan gøre.

## Realisation structures

Måder at konvertere fra en difference equation til en graphical representation.

### Direct form 1

Kan ses på slide 16, hvor man mapper en difference equation direkte.

### Direct form 2

Her introducere man en mellem function $w[n]$ som ligger mellem $x$ og $y$.

Dette giver en kombineret direct form 1, og har den fordel at det kræver mindre memory.

## Scaling

Vil gerne have højst mulig Signal to noise, altså man vil gerne bedst mulig udnytte sin precision.

Overflow inde i systemet er okay, sålænge den totale sum ikke kommer over.

Forskellige typer scaling er muligt for at få god utilization.

 -  Max-value scaling
    Har den ulempe at man kan ende med ikke at udnytte systemet optimalt.
 -  Sinusoid scaling
    Self study
 -  Variance scaling
    Siger man at energi ved input skal være større end ved vigtige steder.

# Topic 11

## DFT

Modsat DTFT som er continuer i frekvens, DTF er deskret i frekvens.

Udledt af DFS, og udregnes med en sum af signalet selv.

$$
X[k] = \sum_{n=0}^{N-1} x[n] W_N^{kn}
$$

Virker også omvendt.

$$
x[n] = \frac{1}{N} \sum_{k=0}^{N-1} X[k] W_N^{-kn}
$$

Her skal X og x være 0 uden for [0, N-1].

# Topic 12

 -  Periodic convolution (slide 7)
 -  God opsummering af DTF (slide 11)

## Finite sequence to periodic

DTF kræver at man har en periodisk i tid signal.
Dette er ikke rigtig sådan virkeligheden fungere.

Istedet tager man N bits fra sig signal og gentager det om og om igen.
Hvis man ikke har nok bits i sit signal til at tage N, kan man zero pad det til N.
