#include "OutputIntensity.h"
#include <iostream>
#include <cuda_runtime.h>
#include "ParameterDefines.h"


OutputIntensity::OutputIntensity(const std::string& n,const std::vector<double> & parameters,
		const unsigned int & Nout):name(n),time_step_number(Nout)
{
	dim = int(width);
	dims.resize(1);
	dims[0] = dim;
	data.resize(dim*time_step_number);
	tmp_matrix.resize(dim*dim);
	current_step = 0;
}
const std::string& OutputIntensity::GetName()
{
	return name;
}
const std::vector<double>& OutputIntensity::GetData()
{
	return data;
}
void OutputIntensity::proceed(const cuDoubleComplex* vec, const std::vector<double> &parameters)
{
	cudaMemcpy(tmp_matrix.data(), vec, dim*dim * sizeof(vec[0]),
				cudaMemcpyDeviceToHost);
	if(current_step == time_step_number)
	{
		std::cout<<name<<": data exceeds allocated memory"<<std::endl;
		return ;
	}
	for(unsigned int n=0; n < dim; ++n)
	{
		data[current_step*dim + n] = tmp_matrix[ n * dim + n].x;
	}
	current_step += 1;
}
const std::vector<size_t>& OutputIntensity::GetDimensions()
{
	return dims;
}
