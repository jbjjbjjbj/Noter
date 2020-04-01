#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import time

# c-mesh limits
limitre = ( -2, 1 )
limitim = ( -1.5, 1.5 )

def lota(c, T, l):
    """
    Implement the ι function used in mangelbrot

    :param c: Complex number from the c-mesh
    :param T: Mangelbrot threshold
    :param l: Iterations
    """

    z = 0
    for i in range(l):
        z = z*z + c

        # Check if we found or z
        if np.abs(z) > T:
            return i

    # If we did not find z, use l
    return l

def mangel(pre, pim, T, l):
    """
    Calculate the mangelbrot image
    (pre, pim) discribes the image size. Use T and l to tune the mangelbrot
    This function uses the global variables limitre and limitim to determine
    the c-mesh range.

    :param pre: Number of real numbers used
    :param pim: Number of imaginary numbers
    :param T: Mangelbrot threshold
    :param l: Iterations
    """
    
    # Preallocate result array
    rs = np.zeros((pre, pim))

    # Calculate scaling variables
    sre = ( limitre[1] - limitre[0] ) / (pre-1)
    sim = ( limitim[1] - limitim[0] ) / (pim-1)

    # Loop all pixels
    for re in range(pre):
        for im in range(pim):
            # Calculate the complex number using the scalers
            c = limitre[0] + limitim[0] * 1j + sre * re + 1j * sim * im
            
            # Calculate the ι
            rs[re,im] = lota(c, T, l) / l

    return rs


start = time.time()
arr = mangel(500, 500, 2, 100)
end = time.time()

plt.imshow(arr, cmap=plt.cm.hot, vmin=0, vmax=1)
plt.savefig("test.png")
plt.savefig("test.pdf")

print(f"Took {end - start} seconds")
