#ifndef __EntanglementKernels_h_
#define __EntanglementKernels_h_
#include "cuComplex.h"

extern void MakeEntanglementMatrix1(const cuDoubleComplex*, double* , const unsigned int&);
extern void MakeEntanglementMatrix2(const cuDoubleComplex*, double* , const unsigned int&);

#endif /*__EntanglementKernels_h_*/
