#!/usr/bin/env python3
# 2020-09-23:s5/sig/mm6/opg/2 

import matplotlib.pyplot as plt
import sys
import numpy as np

lookahead = 100
values = 50

res = np.empty(values)

for n in range(values):
    s = 0
    for k in range(lookahead):
        h = np.exp(-k/8)

        x = 1
        if (n - k) < 0:
            x = 0

        s += x * h
    res[n] = s

x = np.arange(values)

plt.plot(x, res)
plt.show()


