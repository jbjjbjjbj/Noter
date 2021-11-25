
last([X], X).
last([_|XS], X) :- last(XS, X).

/*
last([1,2,3], X) # Bruger regel 2
last([2,3], Y) # Bruger regel 2
last([3], Z) # Bruger regel 1, så Z = 3
# Så Y = Z = 3
# Så X = Y = Z = 3


Okay det er også bare fint at skrive
last([1,2,3],X)
     |
last([2,3],X)
     |
last([3], X)
*/

attach([], E, [E]).
attach([X|XS], E, [X|R]) :- attach(XS, E, R).


/*
Proof search of attach

attach([1,2], a, L)
        |      X = 1, XS = [2], E = a, L = [1|L1]
attach([2], a, L1)
        |      X1 = 2, XS1 = [], E1 = a, L1 = [2|L2]
attach([], a, L2)
        |      E2 = a, L2 = [a]
*/

nat(zero).
nat(succ(X)) :- nat(X).

after(succ(X), X).

leq(zero, Y) :- nat(Y).
leq(succ(X), succ(Y)) :- leq(X, Y), nat(X), nat(Y).

add(X, zero, X) :- nat(X).
add(X, succ(Y), succ(R)) :- add(X, Y, R), nat(X), nat(Y), nat(R).

sub(X, Y, R) :- add(R, Y, X).

min(X, Y, X) :- leq(X, Y).
min(succ(X), Y, Y) :- leq(Y, X).
