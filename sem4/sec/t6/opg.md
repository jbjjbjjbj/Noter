# Opgave til tema 6

## Opgave 1

> Skriv et 3-siders essay hvor I beskriver og sammenligner forskellige tilgange til at analysere store mængder af netværkstrafik.
> Jeg vil gerne at I dække anomaly-baserede metoder, maskinlæringsbaserede metoder og host-baserede metoder.

### Løsning

Stort set alle morderne organisationer og virksomheder har et intranet til intern
kommunikation.
Dette kræver en minimal infrastruktur da stort set alle enheder kan snakke over
ethernet og TCP/IP.
Men når man forbinder alt på et system ender man med et meget sårbart system, da
alt er forbundet over denne forbindelse.

Derfor er det vigtigt at kan overvåget denne forbindelse for at se at der ikke
sker noget mistænkeligt.
Dette kan være en udfordring da mistænkelig trafik hurtig kan drukne i valid trafik.

En af metoderne til at checke store mængder traffik er Anomaly Detection, hvor
man kigger efter ændringer i adfærd.
Denne metode har to faser, træning og testing.
Først lader man systemet se hvordan trafikken normalt ser ud over en længere
periode.
I testing fasen lader man netværket kigge på ændringer fra træningsfasen.
Dette har den fordel at man ikke behøver at hardkode signature for forskellige
angreb.
Til gengæld kan den lettere give false positives hvis der sker en ændring i den
måde netværket bliver brugt på ( fx: En ny maskine bliver koblet på).

Ved Anomaly Detection kan man bruge forskellige metoder til at finde anamolies.
En simpel metode er ved at sammenligne trafikken med forskellige grænser, men disse kan være svære at sætte.
Dette kan man udvide ved at kigge på det mere statistisk.
Man kan også bruge artificial intelligense som tager inspiration fra vores hjerner til at genkende
mønstre.

Maskin læring eller artificial integlligense kan også stå alene i genkendelse af
mistænkelig trafik.
Her træner man sit netværk med en masse traffik man ved kommer fra viruser og angreb,
så den lærer at genkende det.
Derefter vil den give alarm hvis den ser at der er trafik der følger disse mønstre.

Denne metode er forskellig fra Anomoly Detection ved at den prøver direkte at
genkende angreb og ikke så meget ændringer fra normal adfærd.
Derfor kan man argumentere at den ikke har så mange false positives da den er
ligeglad med at der kommer extra normal trafik.

Problemet er at det er svært at finde dataset til at træne sit system med.
Udover dette skal man huske at holde det opdateret med nye angrebs metoder.

I stedet for at kigge på et helt netværk, kan man også flytte synspunktet ned til
den enkle computer.
Her installere man programmer på hver computer til at se om den computer har virus
eller laver mærkelig traffik.
Disse programmer bruger tit signatur detection men kan også udnytte de overstående metoder.

Dette har den fordel at den er installeret på hver enkelt enhed, hvilket betyder
at hver instans skal checke mindre.
Dette er også ulempen da enheder uden virus detection kan unødiggøre resten.
Udover dette har en virus mulighed for at slå virus detection fra, da det kører
på samme maskine.

Her kan man se at hver metode har ulemper og fordele, og det kan derfor tit være
en fordel af bruge flere af metoderne da de så kan supplere hinnanden.

## Opgave 2

> Diskuter de 3 cases, og lav en kort rapport for hver af dem.

Hvordan er det her forskelligt fra opgaven før.
