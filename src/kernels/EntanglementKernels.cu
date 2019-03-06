#include <math.h>
#include "EntanglementKernels.h"
#include "Indexes.h"

//one frequence
#define x1 (vec[DI_r(n,n)] + vec[Da_r(n,n)] + 0.5)
#define x2 (vec[DI_r(n,n)] - vec[Da_r(n,n)] + 0.5)
#define x3 (vec[DI_r(m,m)] + vec[Da_r(m,m)] + 0.5)
#define x4 (vec[DI_r(m,m)] - vec[Da_r(m,m)] + 0.5)
#define x5 (vec[Da_i(n,n)])
#define x6 (vec[DI_r(n,m)] + vec[Da_r(n,m)])
#define x7 ((n==m)?0:(vec[DI_i(n,m)]) + vec[Da_i(n,m)])
#define x8 ((n==m)?0:(-vec[DI_i(n,m)]) + vec[Da_i(n,m)])
#define x9 (vec[DI_r(n,m)] - vec[Da_r(n,m)])
#define x10 (vec[Da_i(m,m)])

__global__ void DeviceMakeEntanglementMatrix(const double* vec, double* matr, const unsigned int nfibs)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
    int shift = nfibs*nfibs;
	if(id < shift)
	{
        int m = id/nfibs;
        int n = id%nfibs;
        if(n > m)
        {
            m += n;
            n = m - n;
            m = m - n;
        }
        double tmp = - x5 * x5 - x10 * x10 + x1*x2 + x3*x4 - 2*x6*x9 + 2*x7*x8;
        tmp = sqrt(2.0*(tmp - sqrt(tmp*tmp - 4.0 * (
                     x5*x5*x10*x10 - x3*x4*x5*x5 + 2*x4*x5*x6*x8 - 2*x5*x6*x9*x10 - 2*x5*x7*x8*x10 + 2*x3*x5*x7*x9 + x6*x6*x9*x9 - x2*x4*x6*x6 - 2*x6*x7*x8*x9 + 2*x2*x6*x7*x10 + x7*x7*x8*x8 - x2*x3*x7*x7 - x1*x4*x8*x8 + 2*x1*x8*x9*x10 - x1*x3*x9*x9 - x1*x2*x10*x10 + x1*x2*x3*x4))) );
        if(tmp > 0.0 && tmp< 1.0 && m!=n)
            matr[id] = -log(tmp)/log(2.0);
        else
            matr[id] = 0.0;
		
	}
}

void MakeEntanglementMatrix(const double* vec, double* matr, const unsigned int& dim)
{
    DeviceMakeEntanglementMatrix<<<dim*dim/64 +1,64>>>(vec,matr,dim);
}

