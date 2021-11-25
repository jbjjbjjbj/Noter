
Xpath is used for quering information in XML documents.
Can also be used with postgresql databases.

When using xpath, we query an abstact document structure.
This is also represented by a nodetree.

NOTE that `/, /something/else` in the slides are two different queries.

# Nodetree

**Document node** is the root of the tree, thus the whole element.
Will often contain document metadata, and will point at a single root element.

**Element** element represent nodes.

# Location Step

Stuff between two `/`'s.
Looks like `${axis}::${node test}[${predicate_1}][${predicate_2}]`

Axis will default to `child`.
But there are many other, which also have abbreviations.

# Funktioner og Expressions

Man kan køre funktioner såsom concat.
Og de kan bruge queries.

```
concat("hej", /med/dig/text())
```

# Spørgsmål

Vil det her give root element flere gange.
```
//course/..
```

Nope det er sets, den vil ikke være der flere gange.
