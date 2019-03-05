#include "OutputIntensity.h"
#include <iostream>
#include <cuda_runtime.h>
#include "IntensityKernels.h"
#include "ParameterDefines.h"


OutputIntensity::OutputIntensity(const std::string& n,const std::vector<double> & parameters,
		const unsigned int & Nout):name(n),time_step_number(Nout)
{
    dim = (unsigned int)(Nfibs);
	dims.resize(1);
	dims[0] = dim;
	data.resize(dim*time_step_number);
    tmp_data = new double[dim];
    //device_output
    cudaMalloc((void**)&device_output, dim * sizeof(device_output[0]));
    current_step = 0;
}
OutputIntensity::~OutputIntensity()
{
    cudaFree(device_output);
    delete[] tmp_data;
}

const std::string& OutputIntensity::GetName()
{
	return name;
}
const std::vector<double>& OutputIntensity::GetData()
{
	return data;
}
void OutputIntensity::proceed(const double* vec, const std::vector<double> &parameters)
{
    MakeIntensity(device_output, vec, dim);
    cudaMemcpy(tmp_data, device_output, dim * sizeof(device_output[0]),
				cudaMemcpyDeviceToHost);
	if(current_step == time_step_number)
	{
		std::cout<<name<<": data exceeds allocated memory"<<std::endl;
		return ;
	}
	for(unsigned int n=0; n < dim; ++n)
	{
        data[current_step*dim + n] = tmp_data[n];
	}
	current_step += 1;
}
const std::vector<size_t>& OutputIntensity::GetDimensions()
{
	return dims;
}
