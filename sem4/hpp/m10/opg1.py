#!/usr/bin/env python3
# Measure the performance of your Python matrix multiplication
import numpy as np
import time

size=1000

a = np.random.random((size, size))
b = np.random.random((size, size))

start = time.time()
result = a @ b
end = time.time()


print(result)
print(f"Took { end - start } seconds")
