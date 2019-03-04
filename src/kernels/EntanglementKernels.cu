#include <math.h>
#include "EntanglementKernels.h"

//one frequence
#define x1 (vec[m*dim+m].x + 0.5)
#define x2 (vec[n*dim+n].x + 0.5)
#define x3 (vec[m*dim+n].x)
#define x4 (vec[m*dim+n].y)

//different frequence
#define y1 (vec[m*dim+m].x)
#define y2 (vec[shift + n*dim+n].x)
#define y3 (vec[2*shift + m*dim+n].x)
#define y4 (vec[2*shift + m*dim+n].y)


__global__ void DeviceMakeEntanglementMatrix1(const cuDoubleComplex* vec, double* matr, const unsigned int dim)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	int shift = dim*dim;
	if(id < shift)
	{
		int m = id/dim;
		int n = id%dim;
		double tmp = x1*x1 + x2*x2 - 2*x3*x3 - 2*x4*x4;
		tmp = sqrt(2.0*(tmp - sqrt(tmp*tmp - 4.0 * ((x3*x3 + x4*x4 - x1*x2)*(x3*x3 + x4*x4 - x1*x2))) ));
		if(tmp > 0.0 && tmp< 1.0 && m!=n)
			matr[id] = -log(tmp)/log(2.0);
		else
			matr[id] = 0.0;
		
	}
}

__global__ void DeviceMakeEntanglementMatrix2(const cuDoubleComplex* vec, double* matr, const unsigned int dim)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	int shift = dim*dim;
	if(id < shift)
	{
		int m = id/dim;
		int n = id%dim;
		double tmp = y1*y1 + y2*y2 + 2*y3*y3 + 2*y4*y4;
		tmp = sqrt(2.0*(tmp - sqrt(tmp*tmp - 4.0 * ((y3*y3 + y4*y4 - y1*y2)*(y3*y3 + y4*y4 - y1*y2))) ));
		if(tmp > 0.0 && tmp< 1.0)
			matr[id] = -log(tmp)/log(2.0);
		else
			matr[id] = 0.0;
		
	}
}

void MakeEntanglementMatrix1(const cuDoubleComplex* vec, double* matr, const unsigned int& dim)
{
	DeviceMakeEntanglementMatrix1<<<dim*dim/64 +1,64>>>(vec,matr,dim);
}

void MakeEntanglementMatrix2(const cuDoubleComplex* vec, double* matr, const unsigned int& dim)
{
	DeviceMakeEntanglementMatrix2<<<dim*dim/64 +1,64>>>(vec,matr,dim);
}
