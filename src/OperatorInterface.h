#ifndef __OperatorInterface_h_
#define __OperatorInterface_h_
#include <cuComplex.h>
#include <vector>

class IOperator
{
public:
	IOperator(){};
	virtual ~IOperator(){};
	virtual void apply(cuDoubleComplex*, const cuDoubleComplex*,
			const std::vector<double>&) = 0;
};

#endif /*__OperatorInterface_h_*/
