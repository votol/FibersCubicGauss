#ifndef __Operator_h_
#define __Operator_h_
#include "OperatorInterface.h"
#include "OperatorElement.h"

class OperatorBase:public IOperator
{
    unsigned int DIM;
    OperatorElement* device_operator;

public:
    OperatorBase(const std::vector<double>&, unsigned int);
	virtual ~OperatorBase();
    virtual void apply(double*, const double*,
				const std::vector<double>&) override;
};

#endif /*__Operator_h_*/
