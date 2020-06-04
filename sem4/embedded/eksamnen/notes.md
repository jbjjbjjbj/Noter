
## J1 module 1

> Show code and explain for 1,4,5,6  (design and impl ISR, time based debouncing, tick routing, limitations)

TODO med arduino.
Og debouncer.

### Noter

Findes forskellige slags realtime afhængig af hvor vigtigt det er at man laver
sin opgave inden for deadline.

- **Hard** er når en manglende deadline tæller som en system fejl.
- **Firm** nogle deadlines på gerne misses, men disse resultater vil være ubrugelige.
- **Soft** et resultat er ikke nær så meget værd hvis det er forsent, men kan stadig bruges.

## H1 module 2

> Exercise 1-11

See ../emb_m2/emb_m2.ino

TODO med arduino

### Noter

**Q-format** er hver man dedikere nogle af bits til decimaler.
Det er derfor ikke *floating* point.

**Floating points** er decimal tak med en floating point.
Her har man kun et bestemt tal betydende cifre.

TODO læs op på error calculus.
Totalt uforståeligt i slides.

Der findes forskellige måder at have negative tal på.

- Signed
    Her bruger man MSB til at betyde sign.
    Når den er 1 er det et minutal.
    Problemet er at der nu er 2 nuller.
- 1's komplement
    Ligesom *signed* men når det er negativt er alle bits flippet.
    Dette gør det meget lettere at lave matematik på det.
    Her er stadig det problem at der er 2 nuller.
- 2's komplement
    Ligesom *1.s komplement* men negative har 1 lagt til.
    Dette betyder at der kun er 1 nul værdi.

## H2 module 3

> Exercise 4-7

TODO lav det her på arduino.

### Noter

To forskellige hoved protokoller.

- ASCII
    Let at læse at læse for en person.
    Det er nemmere at seperere felter.
    Bare ikke særlig efficient.
- Binary
    Inviklet af seperere felter, da data felter kan indeholder delimiters.
    Mere efficient.

Findes fire forskellige structurelle elementer.

- Sequence
    Flere elementer efter hinnanden.
- Alternation
    Enten den ene eller anden type element.
- Repetition
    Lister af det samme elemtn
- Abstraction
    Structure og egne data typer.

**Haming distance** er hvor mange bits er forskellige mellem to bit sekvenser.

**Haming distance of protection code** hvor langt der er imellem to sekvenser
der stadig er korrekte.
Dette kan man kande for *HD*.

- Hvis *HD* er større end *n* kan man detect *n* bit errors.
- Hvis *HD* er større end *2n* kan man fixe *n* bit errors.

Fletcher *HD* er 2 så man kan detect en bit fejl.

## J2 module 4

> Show LED13 blink code and explain program.

> Explain interrupt

> Lack of control maybe bq of non-interruptable ISRs

> Procesmodel: running,ready,blocked

> semaphore wait and signal

## J3 module 5

> What is a semaphore, show code from above and eplaing critical region setup

## J4 module 6

> Show code for and explain message queues as a buffering tool.

## J5 module 6.5

> Exercise 1 in part3 on page295 (Pdf is on moodle)

## H3 module 7

> Exercise 4-5

### Noter

**Scheduling** er når flere opgaver eller jobs skal time shares på en CPU.
Et **Schedule** er plan for hvordan disse opgaver skal have tid.
Et schedule er **feasable** hvis alle jobs kan køres imellem deres readytime og
deadline.

Der findes forskellige kategorier.

- Fixed schedules
    Jobs kører på tidspunkter man har bestemt for forhånd.
    Og dette kører bare i loop.
    Dette er ret simpelt og effektivt men ikke særlig fleksibelt.

    Her behøver man kun lave en plan hen til LCM eller Least Common Multiple af
    tasks periods.
- Round robin
    Fixed tidsrum er delt ud mellem jobs periodisk.
    Simpelt og fleksiblet men ikke effekttivt.
- Fixed priority
    Det er altid jobbet med højeste prioritet der kører.
    Dette er simpelt og fleksibelt, men kun middelt effektivt.
- Dynamic priority
    Her bruger man andre regler til at bestemme hvem der kører.
    Dette giver de bedste resultater men er også mere komplekst.

Utilization er *completion time* dividere med *period*.
Man kan definere CPU utilization som:

$$
U = \sum_{i=1}^N \frac{c_i}{T_i}
$$

*Rate Monotonic Scheduling* eller **RMA** er når man giver task med lav periode
højere prioritet.

## H4 module 8

> Exercise 1-2

## H5 module 9

> All exercises
