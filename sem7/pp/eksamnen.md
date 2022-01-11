
# Spørgsmål

## Scheme Del

  - Er `number?` ikke en higher order function

## Alt Andet

  - "The last condition ..." i logic part 2 1:40. Er det rigtigt?
  - Er det ikke en fejl i 0:32 i prolog lists videon

# Mixed

*Parameters* is in the declaration, and *arguments* are the things actually passed.

## Rewriting Rules

**Alpha** is when the parameters of an expression are renames to a otherwise free name.

**Beta** is the most important as it describes the application of functions.
Here we replace the abstraction like `(lambda ...)` or `sum` and replace it with the body.
The arguments are placed in the body according to the parameters.

**Eta** says that functions that just pass arguments to other functions can be substritued by its body.

## Some Haskell Things

```haskell
-- if
hej = if (x == 10) then 2 else 3

-- List comprehention
evens = [i | i <- [0..], i `mod` 2 == 0]

-- Here True and False are *term contructors* and Boolean is a *type constructor*
data Boolean = True | False
```

# Scheme lek. 1

Programming paradigm
: A pattern that serves as a *school of through* for programming.

Programming technique
: Related to how a problem is solved, one example being divide and conquer.

Programming style
: How to express ourselves with a programming language, relating to elegance and coding style.

Programming culture
: A combination of paradigm, styles, and techniques. Often related to a family of programming langauges.

## Imperative Programming

An incremental change of programming state over time, through an execution of computations is steps.
Very similar to normal recipies such as food etc.

Abstraction for a traditional Von Neumann computer.

## Object Oriented Programming

OOP tries to model after the real world and the human interaction with it.
Here data is *encapsulated* in objects, thereby giving a sense of *information hiding*.
This internal data or the object state is then changes by commands or methods, which are called with *message passing*.

Objects are then grouped in classes, which represent concepts.
Classes are organized with *inheritance* hierachies.

## Functional Programming

Different from imperative programming in that data is unmutable, thereby relying on copies.
Also times plays an very minor role.

### Types Functional Programming

Comes in a typed variant, where every expressions have a vel defined type.
These types can be found *type inference*.

Often provides very powerfull type systems.

## Logic Programming

Very different from all the other in that it is based on mathematical logic (predicate logic).
Here we define the properties of a solution, and not how it is found.
Thereby the language implementation finds the best algorithm and data-structured to use.

## Self-Evaluating

Anything that is not a list or a symbol.
Thus anything that just evaluates to itself such as the string "foo".

For example if the variable `v` maps to `"v"`, does not mean that `v` is self evaluating.
This is becuase `v` and `"v"` is not the same.

Numbers and strings are self-evaluated.

# Scheme lek.2

Referential transparency
: Hvis to expressions er lig hinnanden, kan de også udbyttes med hinnanden.

## Y Combinator

How do we encode loops in lambda calculus.

A loop is something that does nothing but run itself.

```
loop = (x: x x) (x: x x)
```

Her kan vi se at hvis vi tager og applier den anden function is den første, får vi det samme som der var før.
Man kan derfor blive ved med at apply for evigt.

We want to define a general recursive, which we can use to define any recursive function.
Such a function would look like:

```
rec f = f(rec f)
```

Unwinding this will apply the function f infinitely.
Thus we want to encode `rec` without recursion.

The factorial function can then be written as.

```
fac = rec (f: n: if (n == 1) 1 (n * (f (n-1))))
```

Therefore `n * (f (n-1))` is therefore the non recursive part of factorial.

`rec` can be defined with.

```
rec = f: (x: (f x x)) (x: (f x x))
```

This is *y-combinator*.

# Scheme lek.3

Trampolining
: Run multiple computations "simutaniusly" by jumping back and fourth.

## Continuation Passing Style

This is where the return value of a function is parsed to another function instead of returning.

```lisp
(define (add a b k)
    (k (+ a b)))
```

This has several advantages:

  - Function in CSP are always tail recursive.
  - Function in CSP do not need call/cc.

## Meta-Circular Scheme Interpreter

A interpreter written in scheme itself instead of another language like C.

# Scheme lek.4 Evaluation Ordering

It should not matter in which order we apply reductions, as we should always come to the same value or results.
However it may be possible for orderins to newer come to a conclusions, but instead do infinite loops.

**Normal Form** is an expression is on normal when it cannot be reduced further by the use of eta or beta reduction.
Intuitively this is the value of an expression.
A normal form of an expression is unique, however some expressions do not have a normal form.

**Weak Head Normal Form** is close to normal form.
However it is not explained further in the slides.


## Normal Order

Is where the outer leftmode reduction is done first.
Therefore doing an *evaluation by need*.

**Lazy evaluation** is an implementation of normal order reduction, which avoid repeated calculations of subexpressions.

## Applicative Order

The innermost reduction is done first, implementing an *eager evaluation*.

## Church Rosser Statements

> If `e1 <=> e2` then there exists an e3 such that `e1 <=> e3` and `e2 <=> e3`.

Dette betyder at beta og eta conversion er *confluent*.

> If `e0 => ... => en` and `en` is on normal form, then there exists a normal order reduction from `e0` to `en`.

Therefore normal order is the post powerful reduction

## Scheme Delayed Evaluation

`(delay expr)` is used to delay the evaluation of `expr`, by returning a promise.
The value of this can then be extracted with `(force promise)`.

# Haskell lec.5 Lazy Evaluation

Lazy evaluation is the default in haskell.
Semanticly it is quite simple requiring only a small amount of rules.

There is the beta rewrite rule from before.
And then there is *application* rule which states that for an application `e1 e2` we only evaluatate `e1`.
This means that `e2` is newer evaluated before the application is done.

# Haskell lec.7 Type Systems

## Simple Type System

Her har man at expressions kan have simple typer som Int, Bool, eller funktionener og tuples.
Dette giver nogle forskellige garantier.

Hvis `e` er *wel typed* og `e` reducere til `e'`, så er `e'` også vel typed.
Dette hedder **subject reduction** og siger noget om *type preservation*.

Den anden er at hvis `e` er *well typed*, så terminere `e`, altså der er en `e'` som er `e` reduceret og `e'` kan ikke reduceres længere.
Dette er **type safety**.

Disse garantier betyder også at der er mange ting man ikke kan representere.
For eksempel hvad hvis man gerne vil lave programmer der terminere.

Dette kan man sige fordi det imple type system har *slack*.
Dette er fordi der er expressions der er safe, men ikke er vel typed.
For eksempel:

```
let f = x: x; in (f 0, f True)
```

Dette giver bare `(0, True)` men det er ikke well typed, fordi der ikke en type for `f`.

## Parametric Polymorhism

Her introducere man

  - **Type variables** som der kan representere hvad som helst.
  - **Type schemes** som siger noget om free og bound type variables.

Hvis ens type scheme ikke har nogen quantifier for en bestemt type variable, så er den variabel *free*.

Her kan man sige at `Ftv(t)` finder alle frie type variables i typen `t`.
Her kan man også sige `Ftv(E)` for type environment `E` så er resultatet `Ftv(t)` for alle typer `t` i `E`.

### Specialization

Her snakker man om at et type scheme er en specialization af en type.
Så man laver en type fra en type scheme.

Så for eksempel er `Int -> Int \leq \forall a. a -> a`.

### Generalization

Her er det det omvendte, med at man laver en type scheme ud fra en type.
Dette er hvis man har en type har free variable `a`, så kan man lave et scheme der indeholder `\forall a`.

Dette gør man med funktionen `close(E, t)`.
Denne funktion ville tage og lave quantifiers for alle `Ftv(t) \setminus Ftv(E)`.

### Principle Types

En type `t` er principle for expression `e` og type env `E` hvis enten

  - `t` er typen for `e` i `E`,
  - eller typen `t1` for `e` i `E` er en specialization af `t`.

Så man kan kalde principle types den mest generelle type.

Her vil vi gerne have et *type inference algorithm* der finder den principielle type for en expression.

### Semantic Regler

Her introducere man nogle regler der sammen med gamle regler kan identificere typer for expressions.
Dette er `PROJ` som laver specialization, og `GENERALIZATION` som laver generalization.

# Haskell lec.8 More Typing

## Type Classes

With typeclasses, we now say that the quantifiers in a scheme do not say `a can be everything` but `a is part of typeclass \Gamma`.
We use `\Gamma` for a collection of type classes.

Dette betyder at når man normalt bestemte tyder ud fra et environment der mapper Vars til Types,
er der nu også en `C` der mapper fra typevariabler til typeclasses.

Okay tror jeg laver de her noter på papir.
Lidt meget matematik.

# Logic lec.9 Introduction and Datalog

Her skriver jeg igen noter på papir.

# Logic lec.10 Datalog

**Herbrand universe** is the set of constant that appear in the datalog program.
These are the things which we can talk about.

The **Herbrand base** is then the set of all ground atoms that can be created.
This is basicly all the things we can say about the **Herbrand universe**, giving a pretty large set.

## Interpretation

An *interpretation* is a set of atoms from the Herbrand universe.
This could be any subset, and does not have to have to make sense.

We will now talk about how a clause can be true under an interpretation, or how an interpretation models a clause.
Here facts are easy, as we just check if it is contained in the interpretation.
A rule is only false if all the facts in the body are true and the head is false, due to the implicative nature of rules.

## Model

We say that an interpretation is a model for a clause, if every ground instance of the clause is true under the interpretation.
Such an interpretation we denote with M.

We denote the *minimal model* for a program as the smallest possible model for the program.
This mimimal model can be found as the intersection between all models of the program.

We can find it by starting with the empty interpretation, and then repeatedly extend it will all possible conclusions from the program.
First facts are added, and then we will start adding conclusions from rules.
This process will always finish.

## Proof Directed Goal Search

Instead of computing the minimal model, we are only interested in a specific conclusion or query.
This is done with *goal directed proof search*.

This is done by constructing a proof tree.
Here we branch the tree every time we have to choose between two clauses.

## Negation in Datalog

In Datalog we can only negate atoms, and not rules.
Therefore we destinquist negative and positive atoms.
A negative atom can then only appear in the body of a rule and not the head.

Here we extend the idea of when an atom is in an interpretation, such that `I |= not p(t)` holds if `p(t)` is not in `I`.

In datalog we need to do some stuff for stuff to make sense, as we can create programs with multiple incompatible models:

```prolog
P(x) :- not Q(x).
Q(x) :- not P(x).
```

Therefore we want to disallow circularity, which we do by defining layers.
We split the program in subprograms, where each subprogram only refers to things from the preveous layer.
We call this *stratification*.

## Some Words

  - *Model-theoretical* semantics refers to finding a solution with Herbrand universe and base, interpretation and minimal models.
  - *Fixed-point* semantics is the bottom up approach, where we compute the minimal model.
  - *Proof-theoretical* semantics is the top down approach, with proof trees.

These can be shown to be equivalent.

The idea of a minimal model does not make much sense with prolog, as the minimal models can be infinite.

# Logic lec.11 Prolog Instead of Datalog

One should remember that prolog uses proof search instead of computing minimal model.
With proof search and the existence of recursive clauses, the ordering of clauses matters.
This is because the order of clauses determines the order in which proof search tries things.

## Some Short Prolog Things

```prolog
% This mimics the idea of haskells composite types.
nat(zero).
nat(succ(X)) :- nat(X).

% Some list notation
% [1,2,3] er det samme som [1 | [2 | [3 | []]]]
```

The above thing means that the herbrand base is infinite.

## Proof Search

We check each clause in the order in which they appear.
If the head of a clause matches, we unify it with the body of the clause.
We then get new goals which we continue with.
