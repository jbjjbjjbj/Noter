import numpy as np
import multiprocessing as mp

# Local import
from optimised import numpylota

# c-mesh limits
limitre = ( -2, 1 )
limitim = ( -1.5, 1.5 )

def createmangelctx(pre, pim, T, l, savez):
    """
    Calculates the context used when calculating mangelbrot

    :param pre: Number of real numbers in cmatrix
    :param pim: Number of imaginary numbers in cmatrix
    :param T: Mangelbrot threshold
    :param l: Iterations
    """
    sre = ( limitre[1] - limitre[0] ) / (pre-1)

    ctx = (sre, pim, T, l, savez)
    
    return ctx

def mangelstep(ctx, re):
    """
    Calculates a single mangelbrot row.
    
    :param ctx: Context containing information about mangelbrot
    :param re: Row to calculate
    """

    # Unpack context
    (sre, pim, T, l, savez) = ctx

    # Create c-mesh row
    im = np.linspace(limitim[0], limitim[1], pim, dtype=complex)
    np.add(1j * im, limitre[0] + sre * re, im)

    # Calculate ι
    rs = numpyiota(im, T, l, savez)
    if savez:
        return rs
    else:
        # It takes some time to unpack a list of tuples
        # So if no savez do not return a tuple
        return rs[0]

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

    ctx = createmangelctx(pre, pim, T, l, savez)

    # Number of processes
    procs = mp.cpu_count()

    pool = mp.Pool(processes=procs)

    args = ((ctx, i) for i in range(pre)) 
    result = pool.starmap_async(mangelstep, args)
    pool.close()
    pool.join()

    result = result.get()
    if savez:
        z = [None] * pre
        rs = [None] * pre

        # Unzip rs
        for i, r in enumerate(result):
            rs[i] = r[0]
            z[i] = r[1]

        return (np.vstack(rs), np.vstack(z))
    else:
        return (np.vstack(result), None)
