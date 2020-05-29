
# Essay tema 1

Hmm ved ikke om det her bliver et essay.

## Opgave

> Vælg et angreb: Find en beskrivelse og gennemgang et cyberangreb, der har fundet sted, og lav en 2-siders essay dækkende:
> 
>     Hvad der skete
>     Hvem der gjorde det (eller hvem man tror har gjort det)
>     Hvilken type angreb der var tale om
>     Hvilken sårbarhed der blev udnyttet og hvordan det var muligt at gennemføre angrebet
>     Hvordan angrebet kunne have været forebygget
>     Dine egne reflektioner og tanker om angrebet
>     Andre observationer eller kommentarer du synes er relevante

## Noter

NotPetya i to dele EternalBlue og Mimikatz.
Mimikatz trækker passwords ud af memory på win.
EternalBlue bruger en patched blabla
Arbejdede sammen for at sprede sig

NotPetya corrupted boot record

Kun lavet til at smadre

Blev smittet af et penge program som fit indsat virusen.

Ikke opdateret windows, nogle windows 2000. Ikke ordenlig netværks segmentering.

## Kilder

https://www.wired.com/story/notpetya-cyberattack-ukraine-russia-code-crashed-the-world/
https://www.varonis.com/blog/what-is-mimikatz/

## Tekst

Jeg har valgt at skrive lidt om NotPetya angræbet som rystede verden i 2017.
Virusen startede originalt i Ukraine men spredte sig hurtigt til mange dele af verden
og nedlade store virksomheder som Maersk etc.

Angrebet startede ved et Ukrainsk accounting program M.E.Doc som har mange brugere rundt i Ukraine.
Dette program henter periodiske opdateringer af en central server i Kiev, og ved
at indlejre NotPetya i en software opdatering blev den hurtigt spredt til mange computere i Ukraine.

NotPetya ligner ransomware i at det kryptere data på alt enheden, men uden at give brugeren mulighed for at dekryptere det.
Udover dette ødelægger det boot sectoren på computerens harddisk hvilket stopper den i at starte.
Ud fra dette er det ret tydeligt at det ikke er blevet lavet for at ødelægge så meget infrastruktur som muligt.

Virusen bruger to Windows specifikke exploits EternalBlue og Mimikatz.
EternalBlue bruges til at sprede sig til ikke opdaterede computere ved at udnytte
en fejl i Windows SMB protokollen.
Mimikatz bruges til at hente authentication data ud fra RAM på Windows computere,
som den så kan bruge til at logge ind på andre computere.

Dette er en rigtig god kombination da den kan bruge begge exploits til meget hurtigt at sprede sig på et netværk.
Et godt eksempel på dette er da Maersk blev ramt af NotPetya, hvilket lagde virksomheden ned i flere dage.
NotPetya kom ind i Maersk ved at en Ukrainsk medarbejder fik installeret M.E.Doc og fik hentet virusen ned gennem en opdatering.
Derefter spredte virusen sig hurtigt gennem Maersk dårligt segmenterede netværk og lagde alle deres afdelinger ned.

Spredningen var ekstra effektiv eftersom Maersk ikke var gode til at opdatere deres 
computere og ikke gav deres IT afdeling nok budget.

Maersk var ikke alene men de er et godt eksempel på hvad der er galt med mange firmaers
holdning til IT sikkerhed og hvad der kan forbedres.

Udbredelsen af NotPetya kunne være mindsket ved at segmentere netværk så det ikke
kan sprede sig så langt som i Maersk tilfælde.
Og eftersom EternalBlue exploiten der blev brugt var blevet fixet før angrebet,
kunne en opdatering have sænket sprednings hastigheden.

Men det er nemt at sige bagefter og prioriteten har tydeligvis lagt et andet sted.
Til gengæld har dette angreb fungeret som et wakeup call til at det nok er en god
ide at tage IT sikkerhed mere seriøst.

Personligt tror jeg ikke at det er til at undgå at sådan noget sker.
Store firmaer såsom Maersk har rigtig mange computere fordelt over rigtig mange
afdelinger og det er super dyrt at vedligeholde sådan komplekse systemer.
Tror at det kunne være gået meget være da Maersk kunne hente en stor del af deres
systemer tilbage via backup.
