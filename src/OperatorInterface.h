#ifndef __OperatorInterface_h_
#define __OperatorInterface_h_
#include <vector>

class IOperator
{
public:
	IOperator(){};
	virtual ~IOperator(){};
    virtual void apply(double*, const double*,
			const std::vector<double>&) = 0;
};

#endif /*__OperatorInterface_h_*/
