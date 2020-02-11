# Opgave 1

## Exercise 9.2

**T(n) = 3T(n/2) + n**

a = 3
b = 2
d(n) = n

a ? d(b) -> 3 > 2

Svaret er derfor O(n^log2(3)) = O(n^1.59)

**T(n) = 3T(n/2) + n^2**

3 ? 2^2 -> 3 < 4

d(n) = n^2 hvilket betyder at O(n^2)

**T(n) = 8T(n/2) + n^2**

8 ? 2^3 -> 8 = 8

d(n) = n^3 hvilket betyder at O(n^3 log2(n))

## Evercise 9.3

**T(n) = 4T(n/3) + n**

a = 4
b = 3
d(n) = n

4 ? 3 -> 4 > 3

Derfor er svaret O(n^log3(4)) = O(n^1.26)

**T(n) = 4T(n/3) + n^2**

4 ? 3^2 -> 4 < 9

d(n) = n^2 hvilket betyder at O(n^2)

**T(n) = 9T(n/3) + n^2**

9 ? 3^2 -> 9 = 9

d(n) = n^2 hvilket betyder at O(n^2 log2(n))
