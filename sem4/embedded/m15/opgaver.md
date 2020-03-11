# Opgaver

## Find deadlines

**Task 1** er alarmer og er derfor ret vigtig.
Den kan også få en høj prioritet fordi den kører sjælent og hurtigt.
Her kan man måske sætte en deadline på 100mS.

**Task 2** her er det en god ide at man ikke lader bruger vente alt for lang tid, men man kan godt halde det en soft realtime.
En passende deadline kunne måske være 0.6 * 2 = 1.2 sekunder.

**Task 3** dette er også en sporatic task men som tager lidt længere tid at køre, og det er stadig soft realtime.
Her ville en passende deadline nok være 0.6 * 10 = 6 sekunder.

**Task 4** her ville det nok være passende at sætte deadline på den næste sample så 100mS.

**Task 5** samme her med en sampling på 1 sekund.

**Task 6** ikke nær så vigtig men samme her med deadline på 100mS.

## Find priority

Her kan man tage baggrund i DMA men det er vigtigt at huske at Task 5 og 2 kommer til at deles om noget memory.

1. Høj prio
	- Task 1
	- Task 4
	- Task 6
	- Task 2 *er heldigvis ret hurtig. Placere den her på grund af at Task 5 kommer til at venter*
2. Mellem prio
	- Task 5
3. Lav prio
	- Task 3

## Servers

Task 2 and Task 3 will use servers with the deadlines determined above as intervals.

## Feasability

TODO
