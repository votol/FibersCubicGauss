#include "OutputSqueeze.h"
#include <iostream>
#include <cuda_runtime.h>
#include "SqueezeKernels.h"
#include "ParameterDefines.h"


OutputSqueeze::OutputSqueeze(const std::string& n,const std::vector<double> & parameters,
		const unsigned int & Nout):name(n),time_step_number(Nout)
{
    dim_al = 30;
    dim = (unsigned int)(Nfibs);
    dims.resize(2);
    dims[0] = dim;
    dims[1] = dim_al;
    data.resize(dim*dim_al*time_step_number);
    tmp_data = new double[dim*dim_al];
    //device_output
    cudaMalloc((void**)&device_output, dim * dim_al * sizeof(device_output[0]));
    current_step = 0;
}
OutputSqueeze::~OutputSqueeze()
{
    cudaFree(device_output);
    delete[] tmp_data;
}

const std::string& OutputSqueeze::GetName()
{
	return name;
}
const std::vector<double>& OutputSqueeze::GetData()
{
	return data;
}
void OutputSqueeze::proceed(const double* vec, const std::vector<double> &parameters)
{
    MakeSqueeze(device_output, vec, dim, dim_al);
    cudaMemcpy(tmp_data, device_output, dim * dim_al * sizeof(device_output[0]),
				cudaMemcpyDeviceToHost);
	if(current_step == time_step_number)
	{
		std::cout<<name<<": data exceeds allocated memory"<<std::endl;
		return ;
	}
    for(unsigned int n=0; n < dim * dim_al; ++n)
	{
        data[current_step*dim * dim_al + n] = tmp_data[n];
	}
	current_step += 1;
}
const std::vector<size_t>& OutputSqueeze::GetDimensions()
{
	return dims;
}
