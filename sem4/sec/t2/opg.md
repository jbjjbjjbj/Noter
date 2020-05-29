# Opgave for tema 2

## Noter

Kunne sende ud med leds på printer som man filmer udfra.

I billeder som meta data. Såsom dimensions etc.

## Tekst

### Del 1

> Giv et overblik over de vigtigste concepter indenfor covert channels og steganografi.
> Det er et stort område, så I må gerne afgrænse til hvad I har læst om i artiklerne, eller hvis der er et område I synes er særligt interessant. (max en side).


Det er tit at man vil sende noget til en ven eller gemme noget som andre ikke skal have fat i.
Her vil de sikre valg være at kryptere ens data.

Men hvad hvis man ikke kun vil gøre det ulæseligt fra andre, men man vil også gemme det.
Her kan man bruge steganografi metoder til at gemme hemmelig data i ellers normal data.

Dette kan for eksempel være ved at pille ved Least Significant Bits i et billede.
Når en person kigger på billedet set det helt normalt ud, men her kan man gemme en masse data.

Hvis man gerne vil sende en hemmelig besked til en ven kan man bruge en covert channel.
Her bruger man steganografi til at gemme en besked i en normal kommunikations kanal.
Den originale kanal som man gemmer beskeden i kalder man for overt kanal, og kan enten
være en mellem sender og modtager eller en som ikke har noget med den hemmelige besked at gøre.
Sidst nævnte kræver at sender og modtager sidder som mellemmænd.
Der findes også andre konfigurationer som er gjort tydelige af the Prisoner Problem.

Der findes forskellige måder at gemme dataen på, her er nogle få:

- I billeder, video eller lyd. Altså digital media.
- I tekst ved at skifte mellem at bruge forskellige stavefejl også videre.
- Over netværket ved for eksempel at bruge timing af pakker eller ændre protokol felter man normalt ikke bruger.
- Ved at styre hardware, kan man sende beskeder ved for eksempel at tænde og slukke for blæser etc.

Ligeledes findes der også måder at finde eller stoppe disse hemmelige beskeder på.
Her bruges tit statistik til at se at om der findes mønstre i de normale beskeder.
Man kan også scrample de variabler der tit bliver brugt til at sende beskeder over.
Dette tælder også timing hvor man kan indføre tilfældige delays.

### Del 2

> Identificer og beskriv et scenarie, der handler om at enten (1) fortrolige data skal beskyttes, 
> så det sikres de bliver indenfor en organisations netværk eller (2) data relateret til skadelig/illegal aktivitet kan skjules i reelle data.
> Det kan enten være et tænkt scenarie, et scenarie I har hørt om, eller et scenarie I f.eks. kender fra en arbejdssituation.

Lad os sige at der er en kæmpe stor software virksomhed der hedder EvilSoft inc.
De skal til at udgive en ny version af deres netværks client EvilSoft EasyConnect som bruges til at 
forbinde til deres EvilNet.

EvilNet er et proprietær netværk som erstattede det åbne akademisk støttede internet tilbage i 1990'erne.
De fleste mennesker er helt tilfredse med EvilNet da de let kan sende Elektroniske Mails med EvilMail
eller se film på EvilTv.

Trods dette findes der også en stor gruppe som er imod EvilSoft på grund af deres 
aggressive markedføring, censur og manglende frihed.
Dette inkludere Computer enthusiaster, frihedskæmpere, software firmaer og lande.

Denne modstand kender EvilSoft godt og de vil derfor gøre at for at kildekoden til
deres produkter ikke bliver udgivet.
Alle computere der har med udvikling at gøre sidder på et airgapped netværk for at undgå at det bliver lækket via metoder såsom
netværks steganography.

Alle udviklerne er godkendte og har underskrevet diverse underskifter.
Og deres egendele bliver talt og tjekker hver gang de kommer og går.
Alle elektroniske enheder samt storagemedia for ikke tilladt for at undgå data i at blive lækket etc.

De har ikke vurderet at det giver mening at gemme dataen bag stegonografi for hvis
hackere får fat i udviklings computerne kan de også finde dekrypterings programmer.

### Del 3

> Antag I er en person med onde hensigter (insider eller outsider).
> I vil nu gerne have fat i de fortrolige informationer beskrevet i det foregående spørgsmål, og få det ud af organisations netværk.
> Ud fra hvad I har læst om covert channels og steganografi skal I nu beskrive mindst tre forskellige metoder, der kunne være brugbare for at overføre denne information.

Her går jeg ud fra at man har fået adgang til dataen på en eller anden måde og mangler at få det ud.

Her er det ikke muligt at få ud via nettet da det ikke er forbundet ud til.

#### Metode 1

*Prøv at bridge over til en computer med internet.*

Her kan man prøve at skabe en forbindelse til en enhed på et andet netværk via en hardware covert channel.
Det kan for eksempel være med netværks termostater som har indbygget sensor, eller via overvågnings camera.

Problemet er her at man skal have en okay hurtig forbindelse for at få hele kildekoden igennem i
nogenlunde tid.

Disse sidder måske på et andet netværk og hvis man kan skabe en hardware baseret forbindelse kan man fra
enheden sende videre med netværkbaserede metoder.
Afhængig af beskyttelsen EvilSoft bruger kan man gemme data i header eller bruge timing angreb.

#### Metode 2

*Hvis man er i rummet kan man ringe ud hvis der er adgang via telefon.*

Er man i rummet og har adgang til telefon kan man prøve at ringe ud.
EvilSoft er paranoia så de optager sikkert alle samtaler, ud over dette er det nok
begrænset hvem man kan ringe til.

Hvis samtalen bliver overvåget kan man bruge sprog baseret stegonography, som nok vil
være lidt det samme som tekst baseret.
Problemet er at dette vil være upraktisk for at flytte store mængder data.

Er det begrænset hvem man kan ringe til må man sætte en modtager op i virksomheden.
Denne kan være koblet på et mindre begrænset netværk.

#### Metode 3

*Embed data i video.*

EvilSoft har sikkert video camera i den sikrede afdeling.
Hvis man på en måde kan komme ind mellem kamera og modtager kan man indsætte data i billedet
med for eksempel LSB.

Det kan nok ikke ses på skærme der viser optagelser, men kan hentes ud hvis man kan
få adgang til bånd.

Med denne metode kan man få rigtig meget data gennem, da video har rigtig meget data
man kan pille med.

### Del 4

> Identificer hvilke parametre der er relevante for at sammenligne disse metoder.
> Vurder de forskellige metoder på en skala fra 1 (dårlig) til 5 (excellent), og begrund ganske kort jeres vurdering.


Her vil jeg vurdere efter:

- Pålidelighed
    Hvor god er metoden hvis der er støj på kanalen.
- Båndbredte
    Hvor meget data kan man sende igennem.
- Usynlighed
    Hvor let er det at se at der bliver sendt data.
- Kompleksitet
    Hvor let er det at sætte op og gøre.

 |              | Metode 1 | Metode 2 | Metode 3 |
 | ---          | ---      | ---      | ---      |
 | Pålidelighed | 2        | 4        | 4        |
 | Båndbredte   | 1        | 2        | 5        |
 | Usynlighed   | 3        | 1        | 1        |
 | Kompleksitet | 1        | 4        | 3        |

### Del 5

> Antag at I har til opgave at beskytte de fortrolige informationer i jeres organization.
> Hvilke forholdsregler vil I træffe for at beskytte disse data?

Dette afhænger meget af hvad slags data det er.
Hvis det er data der skal bruges overalt er det svært at beskytte da det er over
det hele.

Her vil det give mening at bruge kryptering hvor hver medarbejder skal skrive
kode for at få adgang.

Det er svært at undgå at data bliver sendt ud med stegonography, men jeg ville nok sørge for at
computere der skal tilgå data ikke kan forbinde til computere der ikke skal.
Udover dette ville jeg nok sørge for at normalizere headers i pakker samt blokere
protokoller der ikke er brug for.

Internt i et netværk behøver man ikke kryptering så dette kan man også blokere for
så at kunne overvåge alt hvad der bliver sendt.

Det er også en god ide at normalizere data der bliver sendt til vm'er og containers.
For at undgå at der bliver sendt beskeder over load på computer kan man sørge for at
computeren bliver langsommere med jævne mellemrum.

Dette vil kun gøre forbindelsen mere upålidelig, men tyve kan løse det ved at gå ned på
nogle af de andre kriterier såsom bandwidth eller undetectability.

Vil nok gøre sådan at dem der skal arbejde med det ikke må have telefoner eller storage ting med.
Dette er for at de ikke gemmer fortrolig data på det og tager det med ud.
