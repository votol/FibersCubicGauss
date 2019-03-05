#include "OutputEntanglement.h"
#include "EntanglementKernels.h"
#include <iostream>
#include <cuda_runtime.h>
#include "ParameterDefines.h"

OutputEntanglement::OutputEntanglement(const std::string& n,const std::vector<double> & parameters,
		const unsigned int & Nout):name(n),time_step_number(Nout)
{
    dim = (unsigned int)(Nfibs);
    out_dim = (unsigned int)(Nfibs_calc);;
    dims.resize(2);
	dims[0] = out_dim;
	dims[1] = out_dim;
	data.resize(out_dim*out_dim*time_step_number);
	tmp_data.resize(dim*dim);
    cudaMalloc((void**)&tmp_matrix, dim*dim *sizeof(tmp_matrix[0]));
	current_step = 0;
}
OutputEntanglement::~OutputEntanglement()
{
	cudaFree(tmp_matrix);
}
const std::string& OutputEntanglement::GetName()
{
	return name;
}
const std::vector<double>& OutputEntanglement::GetData()
{
	return data;
}
void OutputEntanglement::proceed(const double* vec, const std::vector<double> &parameters)
{
	if(current_step == time_step_number)
		{
			std::cout<<name<<": data exceeds allocated memory"<<std::endl;
			return ;
		}

    MakeEntanglementMatrix(vec, tmp_matrix, dim);
	cudaMemcpy(tmp_data.data(), tmp_matrix, dim*dim * sizeof(tmp_matrix[0]),
				cudaMemcpyDeviceToHost);
	auto it1 = tmp_data.begin() + (dim/2 - out_dim/2)*(dim + 1); 
    auto it2 = data.begin() + current_step * out_dim*out_dim;
    for (unsigned int peri1 =0; peri1 < out_dim;++ peri1)
        {
        for (unsigned int peri2 =0; peri2 < out_dim;++ peri2)
            {
            *it2=*it1;
            ++it2;
            ++it1;
            }
        it1 += dim - out_dim;
        }
    current_step+=1;
}
const std::vector<size_t>& OutputEntanglement::GetDimensions()
{
	return dims;
}
