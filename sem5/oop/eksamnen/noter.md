# Topic 1

## Four OOP principles

Abstraction
:   Objects can hide implementation details, as with interfaces.

Encapsulation
:   Hide internal information from outside, like with getters and setters.

Inheritance
:   Classes can extend other classes, inheriting their methods.

Polymorphism
:   Speficying interfaces which multiple classes can implement.

# Topic 2

## Class composition

```
A <filled>- B
```

B er en del af A, og B vil ikke kunne fungere alene.
A ejer B.

## Class aggregation

```
A <>- B
```

A har B, men B kan også stå alene.
A bruger B

## Association

```
A --> B
```

A does something with B.


## Exception vs Error

Errors are unrecoverable.

# Topic 3

 1. Use cases
    Shows interfaction between things.
 2. Domain model
 3. Interaction diagrams
    Shows more detailed interactions as a sequence diagram.
 4. Design class diagrams

 This repeats multiple times as the requirements may change under development.
 This is because unanticipated things might occur.

## Use case

These are pretty much as always, but here are some important words.

Actor
:   Who performs operations; a person, organization or computer system.

Scenario
:   What are the required interactions required.

Alternate scenario
:   What happens if something goes wrong. What can go wrong.

## Requirements

These diagrams are used to get the following requirements.

- Functionality: what should the system do?
- Usability: what kind of UI is needed?
- Performance
- Implementation constraints

Domain rules
:   Additional external constraints such as laws etc.


## Domain model

Not a part of design but analysis.

Uses conceptual classes, which are real things not functions or data.

Uses vocabulary of the current domain.

Has associations like, class diagram and are interactions between these real objects.
Examples:

 -  A is part of B, or is contained in B
 -  A is a description of B
 -  A is used by B
 -  A is owned by B
 -  A is owned by B
 -  A is an event affecting B

Only include important association, as this is not a specification.

Can include class attributes, but should not contain complex information.
So a Flight maybe has a destination.


# Topic 5

## GUI

Are:

- Asynchronous
- Components are in containers which are in a layout.

# Topic 8 Interaction and Classes

Creating a design from analysis.

## Mapping objects

Object can be mapped from the interaction design, borrowing names as much as possible.

Objects can have to main responsibilities:

 -  Doing things
    Often methods, ex: Cashier has `scanItem()`.
 -  Knowing things

## Patterns

Patterns are solution which fit multiple problems, such as having a `Listener`.

### Grasp patterns

General Responsibility Assignment Software Patterns.

Main patterns:

 -  Information expert:
    Assign a task to the class which has the most information about it.
 -  Creator:
    B should create an object if it contains, records, uses, or has information about object.
 -  Low coupling:
    Uses encapsulation to define simple interfaces between classes, and passing data using standard formats.
 -  High cohesion:
    Create focused objects, instead of `god` objects. This can be done by keeping responsabilities related.
 -  Controller:
    Handles system input events, to seperate the interface from the main system.

Coupling and cohesion manage class complexity.
Strike a balance between object size and complexity.

### Visibility

Who can see what.
Should avoid global visibility as much as possible.
Achieved using *information hiding*.


# Topic 9 Design Patterns

Common language between developers.

Always code using interfaces and not classes, always accept interfaces.

Prefer object composition instead of inheritance (why use OOP then).

Patterns can be used when designing, following types:

 -  Creational: Creates new objects, hiding the creation process
 -  Structural: Patterns concerning class composition
 -  Behavioral: Communication between classes
 -  Anti-patterns: Design features known to create problems

## Factories

Create objects without exposing creation logic.

Eases polymorphism is the factory decides which type to create, and then cast to interface when returning.

## Singleton

An object which is only created once.
Useful when dealing with drivers or sockets.

1. Object A requests singleton C
2. C is creates as it does not exist, and is returned to A
3. B requests C
4. Existing C is returned to B

Special care must be taken when doing multithreading, and testing is also harder.

## Builder

Construct object in the same way as factories.
Implements a `Builder` interface which is run then the product is needed.

One can then build objects without worrying about complex constructor parameters.

## Adapter

Bridge between two incompatible interfaces.

Should be kept as a minimum as deep layering can complicate design.

## Filter pattern

Implements searching.

## Composite

Contains other instances of the same type.
Useful for creating trees.

## Observer pattern

Listens for events and notifies client.
Often used in gui's.

## Publish subscribe 

Publishers publish messages, and subscribers can subscribe on specific events.
This is orchestrated by a central broker.

## Some anti patterns

 -  *God object* with too many responsibilities
 -  Sequential coupling: methods that must be called in order
 -  Object orgy: unrestricted access to internal variables
 -  Yo-yo problem: too many layers of inheritance
 -  Spaghetti code: too many ad-hoc fixes
 -  Error hiding
 -  Object cesspool: reusing objects with unpredictable state

# Topic 10

What happens after first iteration, so first system has been developed.

Clients may want more features.
Here a good domain model can help, as it will facilitate new features easily.

Interfaces can often help implement new features, as only the implementation must be replaced.

## Maintanance

The implementation after a changed design model.

Much easier with a low coupling.

Should be done on a production branch.

# Topic 11

Talking to databases in java happens with the JDBC api.

## ACID

 -  Atomicity
 -  Consistency
 -  Isolation
 -  Durability

## Testing

Static testing
:   Reviewing code.

Dynamic testing
:   Unit test, integration test and acceptance test.

### Code review

Single or as a team.
Walk through the code, and become familiar with code.

Often af good way to ensure correct documentation and code style.

### White box testing

Testing with knowledge of implementation.

Path testing
:   Does the program reach the correct statements

Data flow testing
:   Do variables have expected values at times

Fault injection
:   How do methods handle invalid input

Condition/decision testing
:   Have all possible outcomes been tested using above

#### Intergration testing

Test modules together, are there any problems.

Bottom-up
:   Start with classes, then modules and end at a full program

Top-down
:   Start from main method, and gradually add components

### Black box

Should not use knowledge of the implementation.

#### Acceptance testing

Test the different use-cases, from the perspektive of the user.

Often done by external testers.

#### Automated unit test

Run through testcases which run small parts of program.

This is done in java using the j-unit testing framework.
