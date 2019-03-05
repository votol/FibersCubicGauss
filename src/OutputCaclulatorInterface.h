#ifndef __OutputCalculatorInterface_h_
#define __OutputCalculatorInterface_h_
#include <vector>

class IOutputCalculator
{
public:
    virtual ~IOutputCalculator(){};
    virtual void proceed(const double* , const std::vector<double> &) = 0;
};

#endif /*__OutputInterface_h_*/
