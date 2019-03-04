#ifndef __OutputEntanglement_h_
#define __OutputEntanglement_h_
#include "OutputInterface.h"

class OutputEntanglementOneFrequency:public IOutput
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
	OutputEntanglementOneFrequency(const std::string&,const std::vector<double> &,
			const unsigned int &);
	virtual ~OutputEntanglementOneFrequency();
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
	virtual void proceed(const cuDoubleComplex* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

class OutputEntanglementTwoFrequency:public IOutput
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
	OutputEntanglementTwoFrequency(const std::string&,const std::vector<double> &,
			const unsigned int &);
	virtual ~OutputEntanglementTwoFrequency();
	virtual const std::string& GetName() override;
	virtual const std::vector<double>& GetData() override;
	virtual void proceed(const cuDoubleComplex* , const std::vector<double> &) override;
	virtual const std::vector<size_t>& GetDimensions() override;
};

#endif /*__OutputEntanglement_h_*/
