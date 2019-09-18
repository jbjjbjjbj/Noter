# Vulnabilites

Using the unsecure propreitary crypto1.
Companies often do this however custom crypto often ends wrong.

Ting der gør crypto1 usikker.

- Kun 48 bits. Dette er et problem da crypto1 er fuldt reversed.
- Random generator til 32 bit nounce er kun 16 bit entropy. 

	Dette betyder at nouncene vil gentage sig rimelig hurtigt, og eftersom den starter i known state kan man time sig til en nounce man kender. 
	
	Dette er heldigvis fixet i senere versioner hvor man har lavet en bedre random generator.
- Nested attack hvor man ud med en ud fra en sector key kan udlede 32 bit fra keystreamen. 

	Her authentikator man til en sector, og laver derefter en nestet authentification. 
	I denne nestet bliver sendt krypteret, men fordi man kan regne ud hvad den er kan man udlede keystream(du ved fordi xor).

- Parity bits deler en keystream bit med den næste bit. Dette betyder at den kan udledes.

	Denne fejl kan ikke fixes let ligesom den med nouncene.

- Keystream fra fejl

	Hvis man sender et forkert svar ved challenge-response, sender den en fejl **kryperet**.
	
	Eftersom man kender fejlkoden kan man få 4 bits fra keystream.

	Denne fejl kan heldigvis fixes da læsere alligevel ikke bruger denne fejlbesked(de kan jo ikke læse den når den er krypteret).

- LFSR rollback

	Hvis man kan udlede LFSR på et eller andet tidspunkt kan man regne ud hvad den var fra i starten, hvis man har det data der er puttet ind.

	Eftersom den starter med at være secret key kan man derfor udelede den.

- Ulige bit filter

	Noget med at filtret der feeder tilbage til LFSR kun bruger de ulige bits.

	Dette betyder at man kan lettere kan komme tilbage til starten af LFSR.
	Forstår ikke helt hvordan.

## Angreb for key

De starter med at hente en masse nounces ind med nestet attack.

Ret avanceret. 
Noget med propability. 
De skriver noget med en sum function jeg ikke helt forstår.
(edit kan se det står længere nede. Ved ikke helt om jeg læser det, der er ret meget. Vi ved der der).

De får nogle forskellige keys det måske kan være.

De kan tage og prøve at dekode alle nouncene med en key for at test den.
De ved at key'en er god når parity passer. 

Hvis parity ikke passer er der 1/2 change for at keyen er god.
