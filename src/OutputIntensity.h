#ifndef __OutputIntensity_h_
#define __OutputIntensity_h_
#include "OutputInterface.h"


class OutputIntensity:public IOutput
{
	std::string name;
	unsigned int time_step_number;
	unsigned int dim;
	std::vector<size_t> dims;
	std::vector<double> data;
	std::vector<cuDoubleComplex> tmp_matrix;
	unsigned int current_step;
public:
	OutputIntensity(const std::string&,const std::vector<double> &,
			const unsigned int &);
	virtual ~OutputIntensity(){};
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
	virtual void proceed(const cuDoubleComplex* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

#endif /*__OutputIntensity_h_*/
