
# Spørgsmål

## Scheme Del

  - Er `number?` ikke en higher order function

## Alt Andet

# Mixed

*Parameters* is in the declaration, and *arguments* are the things actually passed.

## Rewriting Rules

**Alpha** is when the parameters of an expression are renames to a otherwise free name.

**Beta** is the most important as it describes the application of functions.
Here we replace the abstraction like `(lambda ...)` or `sum` and replace it with the body.
The arguments are placed in the body according to the parameters.

**Eta** says that functions that just pass arguments to other functions can be substritued by its body.

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
