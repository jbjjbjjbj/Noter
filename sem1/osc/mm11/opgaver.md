# Opgave 1

Mange af dem er okay.

```
<program> ::= 'program''(' <ident> ')' <statementlist> 'end'.
<statementlist> ::= <statement> <statementlist> | e
<statement> ::= <ident> '=' <exp>;

<exp> ::= <term> <expB>
<expB> ::= <termopr> <term> <expB> | e

<term> ::= <factor> <termB>
<termB> ::= <factoropr> <factor> <termB> | e
<termopr> ::= '+' | '-'

<factor> ::= '(' <exp> ')' | <ident>
<factoropr> ::= '*' | '/'
```

# Opgave 2

Denne laver jeg måske senere.

# Opgave 3
