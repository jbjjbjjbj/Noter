# Opgave 2 til Tema 3

## Vigtigste former for TCP-scanning

**Passiv lytning**
- Tager tid for at få nok data.
- Tigger på hvem der snakker med hvem.
- God da man finder services og hvordan de bliver brugt.
- Stort set umuligt at se at man bliver scannet.

**Open scanning**
- Simpel scan der åbner en masse TCP forbindelser.
- Kan meget let ses af service, da de bliver notificeret.

**Half open**
- Stopper før man har ringet service op.
- Kræver root for at lave non-standart TCP forløb.

SYN/ACK; Stealth men generere false positives. Men er ret hurtig.
**SYN/ACK**
- Endnu mere scrabet end *half open*.
- Kan lave false positives.
- Ret hurtig på grund af lidt data.

**IDLE SCAN**
- Snyder en zombie til at scanne.
- Dette kræver at zombie ikke sender beskeder imens.

**FIN, Xmas og null scan**
- Stealth da den ikke starter TCP sessioner.
- Virker ikke mod windows maskiner og kræver root.

**TCP SYN scan** 
- Bruges til at finde ud af om host er online, kan ikke check porte.
- Stealth, da den blænder ind.
