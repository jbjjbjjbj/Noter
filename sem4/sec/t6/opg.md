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
ligeglad med at der kommer ekstra normal trafik.

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

### Løsning

Her vil jeg lige skrive hvad jeg synes om hver af dem.

#### Anomaly Detection

Anomaly Detection har en kæmpe forvel over for signatur detection at den kan genkende
trusler den ikke har set endnu.
Til gengæld har den en tendens til at måle falsk positiv, for eksempel hvis man skifter
måden man bruger netværket på.
Derfor er det nødvendigt at man har et menneske til at læse alle alarmer igennem
for at se om man skal gøre noget.

Falske positiver kan også minimeres ved hele tiden at holde systemet opdateret med nuværende brug af netværket.

Hvis et angreb ikke er larmende nok til at aktivere systemet vil der ikke komme nogen alarm.
Derfor vil det nok være et god at kombinere det med signaturbaseret.

#### Maskine læring

Dette har den fordel at man ikke behøver at træne et netværk til den enkle
situation men i stedet til hvert slags angreb.

På den måde minder det meget om signatur baseret, og det tager derfor nogle af
ulemperne med.
For eksempel er det lidt et kapløb med malware udviklere om at lave malware og
træne netværk til at se det.

Ved ikke så meget om signatur baseret detection, men kan forestille mig at det
kræver mindre end maskine læring.
Dette ændrer sig måske lidt når man bruger GPU i stedet.

Maskin læring har den fordel af den kan finde på mere avanceret måder end
man kan udtrykke i regular expressions som bruges i signatur detection.

#### Host baseret

Dette er ikke så meget en anden metode men mere et andet sted at bruge det.

Her fordeler man detection ud på alle de forskellige enheder forbundet til netværket.
Dette giver et meget dybere indsigt i ikke kun netværket men også filer og kørende
processor.
Derfor kan det argumenteres at denne metode kan detektere sovende malware som ikke
sender netværks trafik.

Dette afhænger selvfølgelig af detektion softwaren hvor dybt den kigger.
En dyb søgning vil også være en krævende opgave og vil derfor gøre computeren
mindre effektiv i dens egentlige opgave.

Udover dette kan en malware med root access deaktivere virus programmet og på
den måde gøre løsningen ubrugelig.

#### Konklusion

Tror det giver mening bruge en kombination af følgende metoder, da de supplere
hinnanden rigtig godt.

- Signatur eller maskine learning
    Kigger efter kendt malware der gør ting.
    Dette vil også finde mere skjult hardware.
- Anomaly sammen med en person
    Kigger efter ukendte trusler eller andre mærklige ting.
    Nok en god ide at have en person kigge advarsler igennem
- Host baseret
    Kigger efter malware på de enkle enheder.
    Her kigger den på kørende processor og filer på disk.

