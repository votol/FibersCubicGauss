#ifndef __OperatorKernels_h_
#define __OperatorKernels_h_
#include "OperatorElement.h"

extern void ProceedVector(double* out, const double* in,
        OperatorElement* oper, const unsigned int& dim, const unsigned int& Nfibs);
#endif /*__OperatorKernels_h_*/
