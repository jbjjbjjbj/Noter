import numpy as np

def matrixmult(a, b):
    res = np.empty((a.shape[0], b.shape[1]))
    for ic, c in enumerate(b.T):
        for ir, r in enumerate(a):
            res[ir][ic] = np.dot(c, r)

    return res

a = np.random.random((100, 300))
b = np.random.random((300, 100))

print("a")
print(a)
print("b")
print(b)

custom = matrixmult(a, b)

ref = a @ b

print("custom")
print(custom)
print("ref")
print(ref)

if np.array_equal(custom, ref):
    print("Yay they are the same, well done")
else:
    print("Not the same, bummer")
