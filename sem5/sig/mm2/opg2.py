#!/usr/bin/env python

# 2020-09-09/sig/mm2/opg/2 #bb68
# Første del kan findes i #91a6/P.

import matplotlib.pyplot as plt
import numpy as np

class Series:
    def __init__(self):
        self.conditions = []

    def add_condition(self, *args):
        self.conditions.extend(args)

    def evaluate(self, n):
        res = 0
        for cond in self.conditions:
            res += cond(n)
        return res

    def gen(self, r):
        res = np.zeros_like(r, dtype=float)
        # Super inefficient
        for i, v in enumerate(r):
            res[i] = self.evaluate(v)
        return res

    # Uhhh terrible
    def fold(self, s, r):
        res = np.zeros_like(r, dtype=float)

        # Evaluate own for the whole range r
        start = r[0]
        stop = start + len(r)

        # Terribly inefficient
        for i, v in enumerate(r):
            for k in range(start, stop):
                res[i] += self.evaluate(v) * s.evaluate(v - k)
                print(v, k, self.evaluate(v), s.evaluate(v - k))
        return res

print("Starting")

s1 = Series()
s1.add_condition(lambda n: 1 if n >= 0 and n <= 4 else 0)
s2 = Series()
s2.add_condition(lambda n: 1 if n >= 0 and n <= 9 else 0)

n = np.arange(-10, 15)
plt.plot(n, s1.fold(s2, n), "o")
# print(n, s1.fold(s2, n))
plt.show()


