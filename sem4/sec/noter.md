# Noter til hvert emne

## Cyberkriminalitet og forskellige angribere

Forskellige typer malware

- Ransomware
    Låser filer så man ikke kan få adgang til det uden at betale.
    Offer kan lade nogle filer blive låst op for at bevise at de har nøgle.
- Spyware
    Overvåget brugerent computer brug.
    For eksempel hvordan de bruger internettet eller hvilke koder de taster ind.
    Kan tit komme gennem software man downloader fra mærkelige steder på internettet.

Når man bruger internettet kan man hurtigt blive offer for internet theft.
Dette kan ske gennem dating, falske hjemmesider etc.
Her kan de prøve at på fat i informationer om en eller få fat i ens betalings
info.

For at overføre penge for internettet uden at blive opdaget kan man bruge `mules`.
`Mules` kan hente penge ud fra kontoer og sende det til hackere uden at hackerne
bliver opdaget.
Disse kan være betalt men kan også blive snydt til at blive `mule`.

Information theft kan også ske på en støre skala, ved stater eller firmaer.
Her kan man stjæle information ved at lave hacker angreb eller få adgang via malware
eller botnets.

### Click fraud etc.

Her vil man som hacker have brugere til at click på ens link for at få det frem på
google.

Her kan man bruge malware og botnets til at få mange computere til at check på
linket.

Det kan også være for at snyde reklamefirmaer ved klikke på deres reklamer på ens
hjemmeside.

Lignende er *pay-to-install*, her betaler man for at have sit program installeret
over det hele.
Også vil cyberkriminelle installere dette ulovligt på maser af computere, for eksempel
via botnets.

*Spam* er også noget man kan bruge botnets etc. til.
Dette er for at de ikke bliver blokkeret af email providere.

### DDOS

Her er målet at lave et DOS angreb ved at bruge mange computere over hele verden.
Dette kan være normale request eller onde request.
Disse angreb kan komme helt op på 400 gbps.

Disse angreb styres tit af en central enhed, men sker tit ikke i realtime.

Botnets til at lave de her angreb kan også købet online ret nemt.

### Social enginering og infection

*Drive by infection* er når man bliver infected ved bare at besøge en website.
Disse kan være opsat af cyberkriminelle, men også af normale websites der er komprimenteret.

Man kan også blive infected af programmer man downloader som indeholder virus.

Disse to hænger meget sammen med social engineering, hvor man vil have en bruger
til at gøre noget bestemt.
Dette kan være at installere overstående programmer eller hjemmesider for at installere
programmer på deres pc.
Her skal man også snyde dem til at overwrite sikkerheds ting fra OS.

*Phishing* er ligesom social engineering men i stedet vil man gerne have dem til
at afsløre personlig information såsom logins eller betalings info.

Her sender de snyde mails eller links ud til masser er af mennesker, også er der
altid nogle få der hopper på dem.

### Forskellige cyberkriminelle

- Insiders
    Nogle indefra et firma der gerne vil skade firmaet eller have penge.

    Disse har tit ekstra meget information om dem de vil angribe.
- Cyber Kriminals
    Bussiness der gerne vil gøre det for penge.

    Professionelle som er i grupper.
    Mange som er gode i hver sit felt.
- Script kiddies
    Nogle der bare sidder og leget med hacking.
    Disse gør det best fordi det er nysgærige.
- Gray hats
    Nogle der gør det for sjov eller nysgærighed.
    Har ikke noget undt i sinde.
- Hacktivist
    Nogle der har et politisk mål de gerne vil have ud.
- Nation states
    Få information ud af andre lande eller anden cyberkrig.

## Covert channels og steganografi

Se fil ./t2/opg.md.

*Covert channelse* er når man bruger genner information i en valid kanal som kaldes
*overt channel*.

Disse metoder kalder for *stegonography* og der findes mange forskellige.

- I billeder eller video
    Her gemmer man det ved at ændre på information eller metadata i mediaformatet
    som en bruger ikke vil kunne se.
    Dette kunne for eksempel være i LSB bits.
- Netværkslaget
    Da der bliver sendt rigtig meget traffik over nettet er det et godt sted at
    gemme information.
    Her kan man gemme det i ubrugte/optional felter i protokoller, i felter såsom port
    eller ip eller ved at sende pakker med forskellige intervaller.
- Med tekst
    Her gemmer ham en besked i tekst ved at lave stavefejl eller ændre på måder man skriver på.
- Hardware eller OS
    Her bruger man hardware til at snakke med en anden enhed.
    Dette kan være blæsere og en microfon.

    Det kan også være intern i computeren hvor en process vil snakke med en anden
    hvor de kan bruge CPU usage, OS locks og meget mere.
    

## Netværksscanning

Se fil ./t3/opg2.md

Her er det forskellige måder at scanne på men man kan dele dem op to grupper.

- Passive
    Man lytter til alt hvad der foregår på et netværk ved at koble sig på et centralt sted.
    Dette kan være meget svært at opdage og kan give rigtig god information.
- Active
    Her sender man probes ud for at finde ud af hvilke computere der findes og hvilke
    services der kører på dem.

## Trådløs sikkerhed

Inden for cryptologi findes forskellige mål:

- Authentification
    Er modpart virkelig den han påstår han er.
- Confidentiality
    Er modpart og mig den eneste der kan læse den her besked.
- Privacy
    Kan andre se hvem det er der snakker sammen.
- Integrity
    Kan jeg være sikker på at denne besked ikke er blevet ændre undervejs.
- Availability
    Hvor tit kan forbindelse bruges.

Der er forskellige måder at man som angriber kan angribe en forbindelse.

- Interruption
    Her stopper man forbindelse i at komme igennem.
- Interception
    Her kigger man med på forbindelse.
- Modification
    Her ændre man på beskeder som de gør igennem.
- Fabrication
    Her laver man nye beskeder som ligner at de kommer fra en af parterne.

Angreb kan enten være passive hvor man lytter på en forbindelse, eller aktive hvor 
man går ind og ændre på pakker.
Passive angreb er svære at opgave.

### Threat analysis

Her regner man ud hvor rigtig en trussel er ud fra dens *impact* og *likelyhood*.
Derefter kan man kategorisere de forskellige trusler afhængig af hvor vigtige de er.

Man kan finde *likelyhood* ved at kigge på hvor let det er og hvilket motiv nogle ville have.

På samme måde kan man finde *impact* ved at kigge på hvad sådan et angreb vil gøre
ved virksomhed.

### Wireless

Dette er svært da der kan laves mange angreb.

## Grundlæggende værktøjer og metoder til netværksovervågning

Her bruger man tit wireshark.

Hub vs switch.
Kan også bruge en tab eller to netværksinterfaces.

For wireless skal man have promiscous mode.

## Grundlæggende værktøjer og metoder til trafikanalyse

Se t6/opg.md

## Incident response

### Incident response plan

Skal indeholde forskellig information.

- Kontakter
- Escalation kriteria
    Hvordan skal beslutninger tages, og hvem skal tage dem.
- Flowchart
- Conference nummer
- Guide til hvordan man skal lave legal support og HR.

### Incident management

- Vigtigt at man tracker alt hvad der bliver gjort.
- Alle skal holdes opdateret med møder.
- Skal undgå forvirring.

## Attack & Defense
## Risikovurdering: Analyse af cybertrusler, udfordringer og tiltag
