#ifndef __OutputTime_h_
#define __OutputTime_h_
#include "OutputInterface.h"
#include "OutputCaclulatorInterface.h"


class OutputTime:public IOutput, public IOutputCalculator
{
	std::string name;
	unsigned int time_step_number;
	unsigned int dim;
	std::vector<size_t> dims;
	std::vector<double> data;
    unsigned int current_step;

public:
	OutputTime(const std::string&,const std::vector<double> &,
			const unsigned int &);
    virtual ~OutputTime()override;
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
    virtual void proceed(const double* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

#endif /*__OutputTime_h_*/
