# Opgave 1

> Et operativsystem anvenderen 2-level page tabel og 4Kbyte pagesize. Det
virtuelle adresseområde er på 4GByte. De programmer der afvikles på
computeren er på mellem 64 KByte og 16MByte. Hvor mange bit vil I anvende til
index ind i hhv. page tabel 1 og pagetabel 2.

Her betyder det at man har en tabel der referere til level 2 tabeller.

Så i level to tabellen ville jeg nok have 4M da det er 1023 pages. 
Dette betyder at der vil lidt spild med det lille program på 64kb men det større program på 16Mb betøver ikke få så mange pages.

1023 pages kræver tilgængeld 10 bits til indexering hvilket er lidt spild.

For at få op til 4GB skal man igen have 1023 reference i level 1 tabel.

En anden mulighed ville være at have 8 bits til level 2 index, og derfor have 255 pages i level to tabel.
Dette vil betyde at level to indexen ikke spilder plads from med 10 bit.

En level 1 tabel indexer derfor 4Kb * 255 = 4096 * 255 = 104 4480 = 104Kb

Her vil level 1 tabellen få 4Gb / 104.4480Kb = 4 000 000 000 / 104 4480 =~= 4112

Her skal man bruge 13 bits, hvilket betyder at man spilder 3 bits hvis man bruger 16 bit system.

# Opgave 2

> Diskuter måder at håndtere virtuelle pages på. Kan man optimere software i
forhold til hvordan et OS håndterer pages? Er der noget i en eller flere
koncepter I måske kan anvende i jeres projekt?

Læser på wikipedia at dette er en teknik hvor man gemmer under pagene i virtuel memory i stedet for physical.
Dette vil betyder at den også kan blive swappet til disk osv.

Dette vil tilgengeld kræve at man har nogle pages i physical som skal holder styr på de virtuelle som indeholder andre pages.
Det vil nok egentlig være lidt bøvlet. 

Man kunne måske have at level 1 tabellen signalere om pagen er i physical eller virtuel.

# Opgave 3

> Skriv et lille program, der allokerer en stadig voksende mængde hukommelse,
f.eks. start med 8kB, 8MB, 8GB og mere... hvornår løber I ind i problemer?
Observer evt. med værktøjet ovenstående eller andet der passer til jeres
platform.


