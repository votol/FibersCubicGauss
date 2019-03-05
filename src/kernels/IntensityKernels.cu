#include <cuda_runtime.h>
#include <stdio.h>
#include "IntensityKernels.h"
#include "Indexes.h"


__global__ void DeviceMakeIntensity(double* out, const double* in, const unsigned int nfibs)
{
    unsigned int id = blockIdx.x*blockDim.x+threadIdx.x;
    if(id < 256)
    {
        out[id] = 6.0;//in[DI_r(id,id)] + in[al_r(id)]*in[al_r(id)] + in[al_i(id)]*in[al_i(id)];
    }
}

void MakeIntensity(double* out, const double* in, const unsigned int& nfibs)
{
    DeviceMakeIntensity<<<nfibs/64 + 1, 64>>>(out, in, nfibs);
}
