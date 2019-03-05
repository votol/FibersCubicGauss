#ifndef __OutputIntensity_h_
#define __OutputIntensity_h_
#include "OutputInterface.h"
#include "OutputCaclulatorInterface.h"


class OutputIntensity:public IOutput, public IOutputCalculator
{
	std::string name;
	unsigned int time_step_number;
	unsigned int dim;
	std::vector<size_t> dims;
	std::vector<double> data;
    unsigned int current_step;

    double* device_output;
    double* tmp_data;
public:
	OutputIntensity(const std::string&,const std::vector<double> &,
			const unsigned int &);
    virtual ~OutputIntensity()override;
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
    virtual void proceed(const double* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

#endif /*__OutputIntensity_h_*/
