
/* Opgave 1

{
    loves(rose, jack).
    loves(jack, rose).
    loves(caledon, rose).
    happy(rose).
    happy(jack).
}
{
    loves(rose, jack).
    loves(caledon, rose).
}
{
    loves(jack, rose).
    loves(caledon, rose).
}
{
    loves(rose, jack).
    loves(jack, rose).
}
{
    loves(rose, jack).
    loves(jack, rose).
    loves(caledon, rose).
    happy(jack).
}
{
    loves(rose, jack).
    loves(jack, rose).
    loves(caledon, rose).
    happy(rose).
}
{
    loves(rose, jack).
    loves(jack, rose).
    loves(caledon, rose).
}
{
    loves(rose, jack).
    loves(jack, rose).
    happy(jack).
}
{
    loves(rose, jack).
    loves(jack, rose).
    happy(rose).
}
{
    loves(rose, jack).
    loves(jack, rose).
    happy(rose).
    happy(jack)
}

Well okay i feel stupid

We say that the universe U_p = {rose, jack, caledon}.
We will then way that the base is:

U_b = { loves(x, y) | x, y \in U_p } \cup { happy(x) | x \in U_p }

Then all the interpretations are.

I = { S | S \subseteq U_b }

*/


/* Opgave 2

loves(rose, jack).
happy(rose)

happy(rose) <= loves(rose, jack),loves(jack,rose)
We know rose is happy, we do not need to check the predicates.
For some reason, kind of TODO.

*/

/* Opgave 3

I_4 og I_5 er modeller for P, hvor I_4 lige har en extra happy(caledon). 

Her er I_4 minimal fordi ingen anden model for P er mindre.

*/

/* Opgave 4

M_1 = T_P(Ø) = {god(odin),son(odin,thor),son(odin,baldr),son(thor,mothi),son(thor,magni)}
M_2 = T_P(M_1) = M_1 \cup {demigod(thor),demigod(baldr)}
M_3 = T_P(M_2) = M_2 \cup {mortal(mothi),mortal(magni)}

*/

/* Opgave 5

B -+-> A
D -+-> C
B -+-> A
C ---> A
C -+-> B
D ---> B

D, C -> A, B
D -> C -> B -> A

Det er stratifyable.
