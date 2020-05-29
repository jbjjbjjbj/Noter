
# Opgave 1

> Hvad er læringen fra dette angreb? Kunne det have været forebygget, eller kunne man have gjort noget for hurtigere at detektere angreb og dermed afbøde nogle af konsekvenserne?

# Besvarelse

> All he could do was stare helplessly at his screen while the ghosts in the machine clicked open one breaker after another, eventually taking about 30 substations offline.

Jeg er ikke helt inde i kraftværk ting.

I den her situation er det en god ide at have en striks protokol som diktere hvordan vigtige system lukkes ned før mere går galt.
Dette kan desværre være svært da disse procedurer højst sandsynlig er blevet taget højde for af angriberne. 
Derfor er det en slags katten efter musen.

> weren't required to use two-factor authentication, which allowed the attackers to hijack their credentials

Rapporten nævner at sikkerheden generelt var høj på kraftværket, men at login udefra ikke var beskyttet af flere autentifiserings faktorer.
Dette viser rigtig godt hvordan et svagt led kan svække et ellers sikkert netværk.

> Then they wrote malicious firmware to replace the legitimate firmware on serial-to-Ethernet converters at more than a dozen substations

På grund af disse adaptere er så vigtige i styringen af strømmen, have det nok være en god ide at slukke for muligheden for at programmere adapterne over internettet.
Eller have krævet en form for autentifisering på den uploaded firmware, med for eksempel signing af opdateringerne.
