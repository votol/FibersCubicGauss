#include "OutputTime.h"
#include <iostream>
#include "ParameterDefines.h"


OutputTime::OutputTime(const std::string& n,const std::vector<double> & parameters,
		const unsigned int & Nout):name(n),time_step_number(Nout)
{
    dims.resize(1);
	dims[0] = 1;
    data.resize(time_step_number);
    current_step = 0;
}
OutputTime::~OutputTime()
{
}

const std::string& OutputTime::GetName()
{
	return name;
}
const std::vector<double>& OutputTime::GetData()
{
	return data;
}
void OutputTime::proceed(const double* vec, const std::vector<double> &parameters)
{
    if(current_step == time_step_number)
	{
		std::cout<<name<<": data exceeds allocated memory"<<std::endl;
		return ;
	}
	data[current_step] = t;
	current_step += 1;
}
const std::vector<size_t>& OutputTime::GetDimensions()
{
	return dims;
}
