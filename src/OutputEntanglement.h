#ifndef __OutputEntanglement_h_
#define __OutputEntanglement_h_
#include "OutputInterface.h"
#include "OutputCaclulatorInterface.h"

class OutputEntanglement:public IOutput, public IOutputCalculator
{
	std::string name;
	unsigned int time_step_number;
	unsigned int dim;
    unsigned int out_dim;
	std::vector<size_t> dims;
	std::vector<double> data;
    std::vector<double> tmp_data;
	double* tmp_matrix;
	unsigned int current_step;
public:
    OutputEntanglement(const std::string&,const std::vector<double> &,
			const unsigned int &);
    virtual ~OutputEntanglement()override;
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
    virtual void proceed(const double* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

#endif /*__OutputEntanglement_h_*/
