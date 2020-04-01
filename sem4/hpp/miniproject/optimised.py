#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import time

# c-mesh limits
limitre = ( -2, 1 )
limitim = ( -1.5, 1.5 )

def lota(c, T, l):
    z = 0
    for i in range(l):
        nz = z*z + c

        # Check if we found or z
        if np.abs(nz) > T:
            break

        z = nz
    else:
        # If we did not find z, use l
        return l

    return np.abs(z)

def mangel(pre, pim, T, l):
    # Preallocate result array and z array
    rs = np.zeros((pre, pim))
    z = np.zeros((pre, pim))

    # Calculate C matrix
    re = np.linspace(limitre[0], limitre[1], pre)
    im = np.linspace(limitim[0], limitim[1], pim)

    # Calculate C by multiplying the scalers in. Remember to move it to the beggining og the c-mesh limit
    grid = np.add.outer(re, 1j * im)

    for i in range(l):
        z = z*z + grid

        # Extract all the ones that are under the threshold
        below = (np.abs(z) < T)

        rs += below
    
    rs[ rs==rs.max() ] = l
    rs /= l
        
    return rs

start = time.time()
arr = mangel(500, 500, 2, 100)
end = time.time()

plt.imshow(arr, cmap=plt.cm.hot, vmin=0, vmax=1)
plt.savefig("test.png")
plt.savefig("test.pdf")

print(f"Took {end - start} seconds")
