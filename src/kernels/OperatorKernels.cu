#include "OperatorKernels.h"
#include <cuda_runtime.h>
#include <math.h>

__global__ void DeviceProceedVector(double* out, const double* in,
        OperatorElement* oper, const unsigned int dim, const unsigned int Nfibs)
{
    unsigned int id = blockIdx.x*blockDim.x+threadIdx.x;
	if(id < dim)
	{
        out[id] = 0;
        OperatorElement* m_oper = oper + 24 * id;
        for(unsigned int ind = 0; ind < 24; ind ++)
        {
            out[id] += m_oper[ind].coe * in[m_oper[ind].ind1] * in[m_oper[ind].ind2] * in[m_oper[ind].ind3];
        }
	}
}



void ProceedVector(double* out, const double* in,
        OperatorElement* oper, const unsigned int& dim, const unsigned int& Nfibs)
{
    DeviceProceedVector<<<dim/128 +1, 128>>>(out, in, oper, dim, Nfibs);
}

