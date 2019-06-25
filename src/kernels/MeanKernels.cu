#include <cuda_runtime.h>
#include <stdio.h>
#include "MeanKernels.h"
#include "Indexes.h"


__global__ void DeviceMakeMean(double* out, const double* in, const unsigned int nfibs)
{
    unsigned int id = blockIdx.x*blockDim.x+threadIdx.x;
    if(id < nfibs)
    {
        out[id] = in[al_r(id)]*in[al_r(id)] + in[al_i(id)]*in[al_i(id)];
    }
}

void MakeMean(double* out, const double* in, const unsigned int& nfibs)
{
    DeviceMakeMean<<<nfibs/64 + 1, 64>>>(out, in, nfibs);
}
