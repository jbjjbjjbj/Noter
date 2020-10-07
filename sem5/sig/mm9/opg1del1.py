# 2020-04-07:s5/sig/mm9/opg/2 #7d4a

import numpy as np
import matplotlib.pyplot as plt

zeros = [
        [-1, 0],
        [-1, 0],
        [-1, 0],
        ]
poles = [
        [0.4140, 0],
        [0.5225, 0.4525],
        [0.5225, -0.4525],
        ]
pre = 0.0317


def genHamplitude(pre, zeros, poles):
    def f(omega):
        vlen = lambda p: (np.sqrt((np.cos(omega) - p[0])**2 + (np.sin(omega) - p[1])**2))

        top = 1
        for p in zeros:
            top *= vlen(p)
        but = 1
        for p in poles:
            but *= vlen(p)
        return pre * (top/but)
    return f

xs = np.arange(0, np.pi, np.pi/1000)
f = genHamplitude(pre, zeros, poles)
ys = [f(x) for x in xs]

plt.plot(xs, ys)
plt.show()

