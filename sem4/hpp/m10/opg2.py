#!/usr/bin/env python3
# Make a "naive" implementation of a matrix multiplication.
# - Start from the template from last lecture - all global memory, each work item calculates one value of the result independent of the others, and so on.
# - Feel free to make assumptions on the size, for instance that the matrices are square, small enough to fit in GPU memory and so on.
# - Make sure to test your kernel thoroughly enough that you trust it is correct.

# Im asuming that the buffers fit in memory
import numpy as np
import pyopencl as cl
import time

# Source of the kernel itself.
kernel_source = """
__kernel void matrixmult(
             const uint  shared_dim,
    __global const float *a_device, 
    __global const float *b_device, 
    __global       float *result_device)
{
    // get the i'th row of matrix a
    int index_a = get_global_id(0) * shared_dim;

    // get the start of the i'th column of b. 
    // Remember we should index this by jumping b's row size (bcols, or get_global_size(1)).
    int index_b = get_global_id(1);
    int b_jump = get_global_size(1);

    // Do the vector dot
    float result = 0;
    for (int i = 0; i < shared_dim; i++) {
        result += a_device[index_a + i] * b_device[index_b];

        // Remember we need to move b by it's column size to 
        // skip to the next row
        index_b += b_jump;
    }

    // Save the result
    result_device[get_global_id(0) * get_global_size(1) + get_global_id(1)] = result;
}
"""

# matrix a rows
arows = 500
bcols = 1000
# A columns and b rows
shared = 1000

# Create the context (containing platform and device information) and command queue.
context = cl.create_some_context()
cmd_queue = cl.CommandQueue(context)

# Create the host side data and a empty array to hold the result.
a_host = np.random.random((arows, shared)).astype(np.float32)
b_host = np.random.random((shared, bcols)).astype(np.float32)
result_host = np.empty((arows, bcols)).astype(np.float32)

# If you want to keep the kernel in a seperate file uncomment this line and adjust the filename
#kernel_source = open("kernel.cl").read()

# Create a new program from the kernel and build the source.
prog = cl.Program(context, kernel_source).build()

start = time.time()
# Create a device side read-only memory buffer and copy the data from "hostbuf" into it.
# Create as many 
# You can find the other possible mem_flags values at
# https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/clCreateBuffer.html
mf = cl.mem_flags
a_device = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=a_host)
b_device = cl.Buffer(context, mf.READ_ONLY | mf.COPY_HOST_PTR, hostbuf=b_host)
result_device = cl.Buffer(context, mf.WRITE_ONLY, result_host.nbytes)

# Execute the "sum" kernel in the program. Parameters are:
# 
#               Command queue         Work group size   Kernel param 1
#                   ↓   Global grid size   ↓   Kernel param 0  ↓  Kernel param 2
#                   ↓           ↓          ↓       ↓           ↓        ↓
prog.matrixmult(cmd_queue, result_host.shape, None, np.uint32(shared), a_device, b_device, result_device)

# Copy the result back from device to host.
cl.enqueue_copy(cmd_queue, result_host, result_device)

end = time.time()

print(f"GPU time {end - start} sec")


start = time.time()
hostcalc = a_host @ b_host
end = time.time()
print(f"CPU time {end - start} sec")

# Check the results in the host array with Numpy.
print("All elements close?", np.allclose(result_host, hostcalc))
