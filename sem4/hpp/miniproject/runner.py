#!/usr/bin/env python3

import matplotlib.pyplot as plt
import argparse
import os.path as path
import numpy as np
import time
from pathlib import Path
from PIL import Image
import warnings
import h5py

# Many of the implementations overflow some of the values
# This creates warnings which can be ignored
warnings.simplefilter("ignore")

# Implementations
impls = ["naive", "optimised", "multiproc"]

parser = argparse.ArgumentParser(description="runs the different mangelbrot implementations")
parser.add_argument("impl", help="which implementation", default='all', choices=impls + ["all"], nargs='*')
parser.add_argument("--numreal", "--nr", type=int, help="number of real numbers", default=500)
parser.add_argument("--numimag", "--ni", type=int, help="number of imaginary numbers", default=500)
parser.add_argument("--iterations", "-i", type=int, help="mangelbrot iterations", default=100)
parser.add_argument("--threshold", "-t", type=int, help="mangelbrot threshold", default=2)
parser.add_argument("--outputfolder", "-o", help="output folder", default='.')
parser.add_argument("--createpng", help="create png images", action="store_true")
parser.add_argument("--skipz", "-z", help="do not export z", action="store_true")

args = parser.parse_args()

# If no implementations are specified run all
if args.impl == "all" or "all" in args.impl:
    args.impl = impls

def runtest(mangel, name):
    """
    Run test on specified mangel function.
    `mangel` function must be of form

    ```
    mangel(pre, pim, T, l)
    ```

    Uses the global args for options.
    """

    # Run mangel and measure runtime
    start = time.time()
    (rs, z) = mangel(args.numreal, args.numimag, args.threshold, args.iterations, not args.skipz)
    end = time.time()

    plt.imshow(rs, cmap=plt.cm.hot, vmin=0, vmax=1)
    plt.savefig(path.join(args.outputfolder, name + ".pdf"))
    if args.createpng:
        # Convert o simple b/w image
        formatted = (rs * 255).astype('uint8')

        img = Image.fromarray(formatted, mode='L')
        img.save(path.join(args.outputfolder, name + ".png"))

    # Save data as h5py
    h5file = h5py.File(path.join(args.outputfolder, name + ".h5"), "w")
    h5file.create_dataset("result", data=rs)
    if not args.skipz:
        h5file.create_dataset("z", data=z)
    h5file.close()

    return end - start

# Make sure output folder exists
Path(args.outputfolder).mkdir(parents=True, exist_ok=True)

print(f"Running implementations {args.impl}")

for impl in args.impl:
    # Import module
    m = __import__(impl)

    print(f"Running {impl}")
    dur = runtest(m.mangel, impl)
    print(f"{impl} took {dur} seconds")
