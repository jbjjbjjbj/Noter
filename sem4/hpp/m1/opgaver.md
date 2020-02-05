# Opgave 1.3.1

## Del. 2

Ud fra matrix vektor muliplication kan man sige at der ganges N^2 gange.

Også vil man i hver række plus N-1 gang. 
Så der plus'ses `(N-1)*N` gange.

Derfor er der

`2N^2 - N`

Floating point operationer.

## Del. 2

Her vil man bruge output buffer som intermediate variabler.

Derfor vil der være

```
A       x     y
N^2*s + N*s + N*s = (N^2 + 2N) * s
```

# Opgave 1.3.3

```
1.

1 3 5
2 4 6

2.

1 2
3 4
5 6

3.

1 4
2 5
3 6

4. 

1 2 3
4 5 6
```

# Opgave 1.3.4

## Del 1.

m er row count B

A * B = C

```
for column c in B index i:
	for row r in A index j:
		i = c' * r // ' means transponere
		C[j,c] = sum(i)
	end
end
```

# Del 2.

A bliver addresset via kolonner, så det er bedst at bruge column major.

B bliver via rows så det er bedst at bruge row major.

# Del 3.
Yes because we multiply vektors together.

