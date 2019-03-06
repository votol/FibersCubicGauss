#ifndef __OutputSqueeze_h_
#define __OutputSqueeze_h_
#include "OutputInterface.h"
#include "OutputCaclulatorInterface.h"


class OutputSqueeze:public IOutput, public IOutputCalculator
{
	std::string name;
	unsigned int time_step_number;
	unsigned int dim;
    unsigned int dim_al;
	std::vector<size_t> dims;
	std::vector<double> data;
    unsigned int current_step;

    double* device_output;
    double* tmp_data;
public:
    OutputSqueeze(const std::string&,const std::vector<double> &,
			const unsigned int &);
    virtual ~OutputSqueeze()override;
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
    virtual void proceed(const double* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

#endif /*__OutputSqueeze_h_*/
