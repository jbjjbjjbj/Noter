# Opgaver til operativ systemer

Ligenu er det ikke delt op i mapper. 

## Kør mini kernel modul

Compile med make.
Husk at peg makefile på din kernel modul mappe.
Denne er testet på ubuntu server 19.04.

```
make
```

Nu burde der være kommet et jmod.ko som kan loades med.

```
sudo insmod jmod.ko
```

Hvis du får permission denied kan du få flere information ved at checke `dmesg` loggen.

Nu kan du hente major number ind fra dmesg. Led efter `COOL_MODULE:`.
Dette nummer bruger du til at assign den en node

```
sudo mknod /dev/cooldev c MAJOR 0
```

Dette vil map kernel-modul/driver til cooldev i /dev/ mappen.
Husk at skriv til MAJOR nummer fra `dmesg` i stedet for MAJOR.

Hvis man læser man pagen kan man se at det bliver lavet som en character unbuffered file. 
MINOR nummeret er 0 da vores driver alligevel ikke bruger det til noget.
