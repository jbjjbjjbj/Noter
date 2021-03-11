import numpy as np

class MatrixEncoder:
    def ident(dim, value=1):
        return np.identity(dim) * value

class Vector:
    def __init__(self, arr):
        self.arr = arr
        self.len = len(arr)

    def add(self, other):
        return self.__class__(self.arr + other.arr)

    def __str__(self):
        return str(self.arr)

    def print(self, f="{}"):
        print(f.format(self))
        return self

    def gaussian(size, mu, sigma):
        return Vector(sigma * np.random.randn(size) + mu)


class BitVector(Vector):
    def gen_uniform(size):
        arr = np.random.randint(0, 2, size)
        return BitVector(arr)

    def to_int(self):
        reverse = np.flip(self.arr)

        res = 0
        for (i, b) in enumerate(reverse):
            res += b * 2**i
        return res

    def encode(self, matrix):
        return SymbolVector(matrix[self.to_int()])

    def from_int(index, size=None):
        bits = []
        while index > 0:
            remainder = index % 2
            index = index // 2
            bits.insert(0, remainder)

        # Padding if they want
        if size is not None:
            missing = max(0, size - len(bits))
            bits = [0] * missing + bits

        return BitVector(bits)

    def check_if_error(self, other):
        return np.array_equal(self.arr, other.arr)

class SymbolVector(Vector):
    def with_noise(self, c):
        noise = Vector.gaussian(self.len, 0, c)
        return self.add(noise)

    def decide_and_decode(self, matrix):
        dim = len(matrix)
        # Collect all distances in vector
        dists = np.arange(dim)
        for (i, vec) in enumerate(matrix):
            dists[i] = np.dot(self.arr, vec)

        # Find index with smallest
        index = np.argmax(dists)

        # Convert integer back to bit vector
        return BitVector.from_int(index, size=int(np.log2(dim)))

encoder = MatrixEncoder.ident(4, np.sqrt(1))

faults = 0
total = 10000
for i in range(total):
    original = BitVector.gen_uniform(2)
    after = original.encode(encoder) \
        .with_noise(1) \
        .decide_and_decode(encoder)
    if original.check_if_error(after):
        faults += 1

print(f"Fault percentage {(faults / total) * 100}%")

