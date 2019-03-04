#ifndef __OperatorKernels_h_
#define __OperatorKernels_h_
#include "cuComplex.h"

extern void MakeVector(cuDoubleComplex*, const cuDoubleComplex* cons,
		const cuDoubleComplex* ex, double *,const unsigned int&);
#endif /*__OperatorKernels_h_*/
