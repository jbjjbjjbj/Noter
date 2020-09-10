# Opgaver til OOP M2

```
2020-09-10:oop/mm3/opg/1 #5953/G
```

## Opgave 1

```plantuml
left to right direction
actor "Animal owner" as ao
actor "Database" as db

package "Animal hotel" {
    usecase "Make reservation" as umr
    usecase "Check info" as uci
    usecase "Host animal" as uha
    usecase "Return animal" as ura

    (umr) .> (uci) : <<include>>
    (uha) .> (uci) : <<include>>
}

ao --> umr
uci --> db
ao --> uha
ao --> ura
uha --> db
ura --> db
```

## Opgave 2

## Opgave 3