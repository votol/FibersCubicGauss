#include <cuda_runtime.h>
#include <stdio.h>
#include <math.h>
#include "IntensityKernels.h"
#include "Indexes.h"


__global__ void DeviceMakeSqueeze(double* out, const double* in, const unsigned int nfibs, const unsigned int nalph)
{
    unsigned int id = blockIdx.x*blockDim.x+threadIdx.x;
    if(id < nfibs * nalph)
    {
        unsigned int n = id / nalph;
        unsigned int m = id % nalph;
        double alph = 2 * M_PI * double(m) / (double(nalph));
        out[id] = 0.5 + in[DI_r(n,n)] + in[Da_r(n,n)]*cos(alph) + in[Da_i(n,n)] * sin(alph);
    }
}

void MakeSqueeze(double* out, const double* in, const unsigned int& Nfibs, const unsigned int& nalph)
{
    DeviceMakeSqueeze<<<Nfibs * nalph/64 + 1, 64>>>(out, in, Nfibs, nalph);
}
