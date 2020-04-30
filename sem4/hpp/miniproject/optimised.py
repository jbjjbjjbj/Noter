import numpy as np
import matplotlib.pyplot as plt
import time

# c-mesh limits
limitre = ( -2, 1 )
limitim = ( -1.5, 1.5 )

def numpyiota(grid, T, l, savez):
    """
    Calculates the ι using numpy arrays.
    This works with both numpy.arrays and numpy.ndarrays
    Also devides by l
    
    :param grid: c-mesh. Shape will be used to make result
    :param savez: Return z as the second element of returned tuple
    """
    # Preallocate result array and z array
    rs = np.zeros(grid.shape)
    z = np.zeros(grid.shape)

    # Calculate ι for all complex numbers
    for i in range(l):
        # This will generate warnings for some of the values rising above T.
        # Because these values become NAN they are not used, thus the warnings
        # can be ignored
        z = z*z + grid

        # This will generate 1 in all the places 
        # where z < T and zeros elsewhere
        below = (np.abs(z) < T)

        # Add this to the result
        # Because the ones that pass T are 0 
        # they will stop counting.
        #
        # If a specific z never reaches >= T its value in rs will
        # be l
        rs += below

    rs /= l

    if not savez:
        z = None
    return (rs, z)

def mangel(pre, pim, T, l, savez):
    """
    Calculate the mangelbrot image
    (pre, pim) discribes the image size. Use T and l to tune the mangelbrot
    This function uses the global variables limitre and limitim to determine
    the c-mesh range.

    :param pre: Number of real numbers used
    :param pim: Number of imaginary numbers
    :param T: Mangelbrot threshold
    :param l: Iterations
    :param savez: Return z as the second element of returned tuple
    """

    # Used to calculate c-mesh
    re = np.linspace(limitre[0], limitre[1], pre)
    im = np.linspace(limitim[0], limitim[1], pim)

    # Calculate c-mesh
    grid = np.add.outer(re, 1j * im)

    # Calculate ι
    return numpyiota(grid, T, l, savez)
