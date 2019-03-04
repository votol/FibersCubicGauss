#include "OperatorKernels.h"
#include <cuda_runtime.h>
#include <math.h>
#include "ParameterDefines.h"

__global__ void DeviceMakeVector(cuDoubleComplex* vec, const cuDoubleComplex* cons,
		const cuDoubleComplex* ex, double * parameters,const unsigned int dim)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	if(id < dim)
	{
		vec[id].x = cons[id].x + ex[id].x * exp(-D*t); 
		vec[id].y = cons[id].y + ex[id].y * exp(-D*t);
	}
}



void MakeVector(cuDoubleComplex* vec, const cuDoubleComplex* cons,
		const cuDoubleComplex* ex, double * params,const unsigned int& dim)
{
	DeviceMakeVector<<<dim/128 +1, 128>>>(vec,cons,ex,params,dim);
}

