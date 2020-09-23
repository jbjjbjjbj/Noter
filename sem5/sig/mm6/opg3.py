#!/usr/bin/env python3
# 2020-09-23:s5/sig/mm6/opg/3 #cc7f

import matplotlib.pyplot as plt
import numpy as np
import sys

# Load data
data = []
with open(sys.argv[1], "r") as f:
    for line in f:
        data.append(float(line))

data = np.array(data)
datalen = len(data)

x = np.arange(datalen)
before = plt.subplot(2, 1, 1)
after  = plt.subplot(2, 1, 2)
before.plot(x, data)

res = np.empty(datalen)

for i in range(datalen):
    last = res[i-1] if i > 0 else 0
    res[i] = np.exp(-1/8) * last + 1/8 * data[i]

after.plot(x, res)
plt.show()
