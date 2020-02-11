# Opgave A

Hmm ved ikke lige med projekt men har en fed ide.

Openscad men til 2d graffik som **kompilere** til svg.

Tænker at man vil lave det i et sprog som c, go eller rust. 
Rust ville være optimalt men det er også lidt svært.

Det skulle være et emperisk sprog med variabler og functioner.
Funktioner returnere ikke noget, men mere en bestemt figur.

Variables can be strings, floating point numbers.

Lists are defined as list.

Strings begin with big letters. 

Bools are defined as numbers 0 and 1.

Lists are defined as [] and contain all numbers or all strings.

C style comments.

```
var Black = "#FFFFFF";
var White = "#000000";
list Names = [ "nice", "nice2" ];

var radius = 10.2;

func coolCircle(r, Name) {
	// Defined as circle(radius, fgCol, bgCol)
	circle(r, Black, White);

	// Defined as insertText(Text, allign, fgCol)
	insertText(Name, ALIGN_CENTER, Black);
}

translate(1, 2) {
	coolCircle(radius / 2, Names[0]);
}

coolCircle(radius, Names[1]);
```

The code will generate two circles, one in the center and one on the coordinates 1, 2.

# Opgave B

Der er defineret to globale variabler, men de er ikke på stacken.

Inde i main laver man en pointer til a og sender ind i funktionen.
Dette betyder at denne pointer enten ligger på stacken eller i et register når funktionen ainc kører.

Men der kan siges sikkert at stacken indeholder en return pointer til main og en reference til den tidelige stack(tror jeg).


## Kode i assembly

Jeg har ikke taget højde for integer operationer.

```
JMP main
var_a: DB 4

ainc:
	MOV B, [A]
	ADD B, 1
	MOV [A], B
	RET

main:
	MOV A, var_a
	CALL ainc

	HLT
```

## Forskellige compile trin

Proprocessor har ikke noget at lave.

Start med at compile til assembly:

Læg a og b i starten af programmet.

Compiler funktionen ainc og adec og sæt en label ved dem.
Dette gøres ved først at lave koden der henter argument ud og gemmer tidligere stack pointer.
Derefter compiles indholdet i funktionen.
Slut af med at returner til caller.

Derefter bliver assembly'en assemblet:

De forskellige mnenorics(eller hvad det nu hed) bliver lavet om til opcodes og lags sammen med deres argumenter.
Dette gøres for alle funktionerne.

a og b bliver placeret i filen.

Derefter placeres main ved entrypoint og de to funktioner bliver lagt ved siden af.
De forskellige referencer til funktioner og globale variabler bliver byttet ud med deres virkelige værdier i binary.

# Opgave C

Grammastart -> *Viggo* stmList *End*
stmList -> stm stmList | e
stm -> ident *=* exp *;*
ident -> letter symList
letter -> *a* | ... | *å* | *A* | ... | *Å*
digit -> *0* | ... | *9*
symbol -> letter | digit
symList -> symbol symList | e
exp -> term expB
expB -> termopr term expB | e
termOpr -> *+* | *-*
term -> factor termB
termB -> factorOpr factor termB | e
factorOpr -> _*_ | _/_
factor -> *(* exp *)* | ident

## C.2

See tree.png

## C.3




