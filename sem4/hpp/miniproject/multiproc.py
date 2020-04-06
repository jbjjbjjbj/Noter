#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import time
import multiprocessing as mp
from multiprocessing import RawArray

# c-mesh limits
limitre = ( -2, 1 )
limitim = ( -1.5, 1.5 )


def worker(gridchunk, s, step, T, l):
    global rs
    # Preallocate z array
    rschunk = rs[s : s + step]

    z = np.zeros(rschunk.shape)
    print(f"rschunk.shape: {rschunk.shape}, gridchunk.shape: {gridchunk.shape}, T: {T}, l: {l}")

    # Calculate ι for all complex numbers
    for i in range(l):
        # This will generate warnings for some of the values rising above T.
        # Because these values are above T they are not used, thus the warnings
        # can be ignored
        z = z*z + gridchunk

        # This will generate 1 in all the places 
        # where z < T and zeros elsewhere
        below = (np.abs(z) < T)

        # Add this to the result
        # Because the ones that pass T are 0 
        # they will stop counting.
        #
        # If a specific z never reaches >= T its value in rs will
        # be l
        rschunk += below

    np.divide(rschunk, l, out=rschunk)

def mangel(pre, pim, T, l, workers):
    """
    Calculate the mangelbrot image with multiple processes
    (pre, pim) discribes the image size. Use T and l to tune the mangelbrot

    This will split the image in horizontal parts and distribute it 
    between the workers.
    Because the result array is row major, data will be nicely together if
    the workers work with rows not columns.

    Pre must be devisible by workers.

    The result is saved in rs. Sorry couln't get numpy references through to the process as arguments

    :param pre: Number of real numbers used
    :param pim: Number of imaginary numbers
    :param T: Mangelbrot threshold
    :param l: Iterations
    :param workers: Number of workers. 
    """

    # Used to calculate c-mesh
    re = np.linspace(limitre[0], limitre[1], pre)
    im = np.linspace(limitim[0], limitim[1], pim)

    # Calculate c-mesh
    grid = np.add.outer(re, 1j * im)

    # Calculate the partition variables
    step = int(pre / workers)


    # Loop chunks and start the workers
    wl = []
    for s in range(0, pre, step):
        gridchunk = grid[s : s + step]
        p = mp.Process(target=worker, args=(gridchunk, s, step, T, l))
        wl.append(p)
        p.start()

    # Wait for them to be done
    for p in wl:
        p.join()

    return rs

rs = np.full((500, 500), 0.5)

start = time.time()
arr = mangel(500, 500, 2, 100, 1)
end = time.time()

plt.imshow(arr, cmap=plt.cm.hot, vmin=0, vmax=1)
plt.savefig("mult.png")

print(f"Took {end - start} seconds")
"""
        p = mp.Process(target=worker, args=(rs[s:s + step], grid[s:s + step], T, l))
        wl.append(p)
        p.start()

    # Wait for them to be done
    for p in wl:
        p.join()
"""
