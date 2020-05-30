# Opgave 1

> In encryption using block-cipher, what potential problem can occur when using Electronic Code Book? Using Cipher Block Chaining?

## Electronic Code Book

Her er problemet at to beskeder med den samme key giver det samme output.
Derfor kan man pludselig se at to beskeder er det samme ud fra cipher.
Dette er et problem med tekst eller billeder der tit er det samme.

## Cipher Block Chaining

Her er problemet at man ikke kan komme ind i midten af en besked, da man mangler data fra den sidste.
Langsommere da messages afhænger af hinnanden.

Angribere kan pille i bits med den næste besked.

# Opgave 2

> Assume that two parties know each other’s public keys.
> If one message is sent from A to B, what can be verified?

Hvis beskeden er signed af med A's private key kan B check om beskeden virkelig
stammer fra A (her går man ud fra at det kun er A der har A's private key).

Hvis beskeden er krypteret med B's public key kan B være sikker på at ingen andre
har læst beskeden (her går man igen ud fra at ingen kender B's private key).

> If two messages are exchanges, what can be verified? 

Hvis der er to beskeder altså A -> B og B -> A, kan A sikre sig at B har 
modtaget ens besked.
B ved til gengæld ikke om dens besked kom ordenligt igennem. 

# Opgave 3

> With Diffie-Hellman key exchange is a man-in-the-middle attack possible?

Ja det kan man godt, diffie helman viser kun hvordan jo kan blive enige om en fælles key
men ikke hvordan de ved at de snakker til den rigtige.
Derfor kan man som mellemmand lade som om man er B for A og A for B.

# Opgave 4

> Assume the following scenario: A and B both have the knowledge of a secret key K (e.g. pre-shared).
> They communicate over an unsecure channel.
> Define a protocol (by writing down a message sequence chart) in which A and B use the pre-shared key K to mutually authenticate each other and to agree on a common session key (different from the long-term pre-shared key K).
> Try to keep the number of exchanged messages as low as possible.

```
     ┌─┐                                      ┌─┐
     │A│                                      │B│
     └┬┘                                      └┬┘
      │        Tilfældig challenge CA          │
      │───────────────────────────────────────>│
      │                                        │
      │E(K, Tilfældig key KB + E(KB, CA)) + CB │
      │<───────────────────────────────────────│
      │                                        │
      │  E(K, Tilfældig key KA + E(KA, CB))    │
      │───────────────────────────────────────>│
      │                                        │
    ╔═╧════════════════════════════════════════╧═╗
    ║Shared key KT generes med KB xor KA        ░║
    ╚════════════════════════════════════════════╝
     │A│                                      │B│
     └─┘                                      └─┘
```

Her sikrer man ved challenges at A og B er den rigtige og ikke en mellemmand.
KB og KA krypteres med K for at sikre at de ikke bliver læst samt kryptere man
CA og CB med de tilfældige keys for at sikre at de har det samme.

[Kilde til figur](http://www.plantuml.com/plantuml/png/ROv13e9034NtFSLVEX4km8BG4bSivG94AX278HdGw8MyY1UpP3OktBM_hw-jrgsBsttsn7af1Th9Npzltqy3BcFdlOP1KJD9NdA1qw79Vf6Rlj08Zlj0CkESiwQM9FkB2oUS3HVdA2oROdbeX2L2vx6BsYTnYq63HbqnMsHtdaj4mwIXnxv6bLNs-XS0)
