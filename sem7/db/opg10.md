# Exercise 1

**A)** Hvis vi gerne må hente ting fra Shop, kan vi løse det med en join.

```sql
SELECT State, SUM(Count)
FROM TotalSales, Shop
WHERE TotalSales.ShopID = Shop.ShopID
GROUP BY State
```

**B)** Det kan vi ikke, da vi skal bruge MAX(price) hvilket man ikke kan få fra SUM(price).

**C)** Nej det kan vi ikke, fordi TotalSales ikke har DayID. Den har bare Total over altid.

**D)** Men den her kan vi godt.

```sql
SELECT State, Genre, SUM(Price), SUM(Count)
FROM TotalSales, Book, Shop
WHERE TotalSales.ShopID = Shop.ShopID AND TotalSales.BookID = Book.BookID
GROUP BY State, Genre
```

# Exercise 2

Gender=Male    : 1100101
Gender=Female  : 0011010
Office=London  : 1001100
Office=Glasgow : 0100010
Office=Cardiff : 0010001
Title=Dev      : 1010011
Title=Tester   : 0101000
Title=Man      : 0000100

**A)**

And 0011010 
med 1010011
  = 0010010

Så det er row 3, 6

**B)**

Not 0010001
  = 1101110

Så det er row 1, 2, 4, 5, 6

**C)**

And 1101110
med 0011010
  = 0001010

Så det er row 4, 6

**D)**

And 1010011
med 1001100
  = 1000000

Det er row 1

# Exercise 3

Det vil ikke give så meget mening at have 3000 forskellige indexes.
Hvis der for eksempel kun er 300 mennesker, vil det slet ikke give mening.

**B)**

[0;1000)   : 10100000
[1000;2000): 01001010
[2000;3000): 00010101

**C)**

Ja indexen kan hjælpe, men man skal have et refinement step.
Man starter med at finde alle i [1000;3000), også kan man sortere resten fra manuelt.

# Exercise 4

Step 0: A

B: 4 * 200 = 800
C: 4 * 520 = 2080
D: 4 * 100 = 400
E: 2 * 580 = 1160
F: 2 * 595 = 1190
G: 2 * 590 = 1180
H: 1 * 599 = 599
Step 1: C
Step 2: G
Step 3: B

Space: 600 + 80 + 10 + 400 = 1090
Time: 
A = 0
B = 0
C = 0
D = 600
E = 80
F = 80
G = 0
H = 10
Total: 600 + 80 + 80 + 10 = 770

# Exercise 5

**A)**

1(1)
2(1)
7(1)

**B)**

1(1)
2(1)
7(1)
3(2)

**C)**

1(1)
2(1)
7(1)
3(2)
4(1)

**D)**

1(1)
2(1)
3(2)
4(1)

# Exercise 6

**A)**
<g, sum, count>

alpha, 100, 3
beta,  40,  1
gamma, 25,  2
delta, 10,  1

**B)**

alpha, 100, 3
beta,  0,   2
gamma, 25,  2
delta, 10,  1

**C)**

alpha, 100, 3
beta,  0,   2
gamma, 35,  3
delta, 10,  1

**D)**

alpha, 100, 3
beta,  0,   2
gamma, 15,  1

**E)**

alpha, 100, 3
beta,  0,   2
gamma, 15,  1
epsilon, 0, 1

# Exercise 7

Gender=Male    : 1100101
Gender=Female  : 0011010
Office=London  : 1001100
Office=Glasgow : 0100010
Office=Cardiff : 0010001
Title=Dev      : 1010011
Title=Tester   : 0101000
Title=Man      : 0000100

Glasgow : 01,101
Man     : 11000
Male    : 00,00,100,01

