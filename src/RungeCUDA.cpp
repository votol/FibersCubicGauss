#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <fstream>
#include "RungeCUDA.h"
#include "ParameterDefines.h"
#include <iostream>

int GetDim(const std::vector<double>& parameters)
{
	return int(width)*int(width)*6;
}

int RungeCUDA::Get_temperature(void)
    {
    system(("nvidia-smi>/tmp/"+file_uuid + ".inf").c_str());
    std::ifstream is("/tmp/" + file_uuid + ".inf");
    std::string line;
    std::string res;
    std::size_t found;
    while(std::getline(is, line))
        {
        found=line.find(std::to_string(CudaDeviceNumber)+"  GeForce");
        if(found!=std::string::npos)
            {
            std::getline(is, line);
            res = line.substr(8,2);
            is.close();
            system(("rm /tmp/"+file_uuid + ".inf").c_str());
            return std::stoi(res);
            }
        }
    return 0;
    }


int RungeCUDA::interruption(void)
    {
	t2 = std::chrono::high_resolution_clock::now();
	if(std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()>20000)
        {
        int lower_temperature_limit, upper_temperature_limit;
        lower_temperature_limit = 75;
        upper_temperature_limit = 80;
        int temperature;
        temperature = Get_temperature( );
        int i = 0;
        if( temperature >= upper_temperature_limit ){

            do{
                i++;
                std::this_thread::sleep_for (std::chrono::seconds(1));
                temperature = Get_temperature();
            }while( temperature > lower_temperature_limit );
            }
        t1=t2;
        return i;
        }
    return 0;
    }


void RungeCUDA::one_trajectory(void)
{
	double current_output=0.0;
	int output_number = 0;
	unsigned int peri;
	cuDoubleComplex koe;
	koe.y=0.0;
	for(peri=0;peri<Nsteps;++peri)
	{
		if(int(current_output)>=output_number)
		{
			for(auto it = outputs->begin();it!=outputs->end();++it)
				(*it)->proceed(vectors,*parameters);
			output_number++;
		}
		cublasZcopy(blas_handle,DIM,vectors,1,vectors + DIM,1);
		(*operator_pointer)->apply(vectors +2*DIM, vectors,*parameters);
		koe.x=dt/6.0;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + DIM,1);
		cublasZcopy(blas_handle,DIM,vectors,1,vectors + 3*DIM,1);
		koe.x=dt/2.0;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + 3*DIM,1);
		(*parameters)[0] += dt/2.0;
		(*operator_pointer)->apply(vectors +2*DIM, vectors + 3*DIM,*parameters);
		koe.x=dt/3.0;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + DIM,1);
		cublasZcopy(blas_handle,DIM,vectors,1,vectors + 3*DIM,1);
		koe.x=dt/2.0;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + 3*DIM,1);
		(*operator_pointer)->apply(vectors +2*DIM, vectors + 3*DIM,*parameters);
		koe.x=dt/3.0;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + DIM,1);
		cublasZcopy(blas_handle,DIM,vectors,1,vectors + 3*DIM,1);
		koe.x=dt;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + 3*DIM,1);
		(*parameters)[0] += dt/2.0;
		(*operator_pointer)->apply(vectors +2*DIM, vectors + 3*DIM,*parameters);
		koe.x=dt/6.0;
		cublasZaxpy(blas_handle,DIM,&koe,vectors +2*DIM,1,vectors + DIM,1);
		cublasZcopy(blas_handle,DIM,vectors+DIM,1,vectors,1);
		current_output += output_coe;
		interruption();
	}
}

RungeCUDA::RungeCUDA():dt(0.0),Nsteps(0),Noutputs(0),Nrelaxations(0),CudaDeviceNumber(0),parameters(NULL),
				operator_pointer(NULL), init_state(NULL),outputs(NULL),output_coe(0.0)
{
	DIM = 0;
	t1 = std::chrono::high_resolution_clock::now();
	t2=t1;
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	file_uuid = boost::uuids::to_string(uuid);
	vectors = NULL;
	cublasCreate(&blas_handle);
}
RungeCUDA::~RungeCUDA()
{
	cublasDestroy(blas_handle);
}
void RungeCUDA::Calculate(void)
{
	DIM = GetDim(*parameters);
	cudaMalloc((void**)&vectors, 4*DIM*sizeof(vectors[0]));
	output_coe = double(Noutputs)/double(Nsteps);
	(*parameters)[0] =0.0;
	cudaMemcpy(vectors, init_state->data(),DIM*sizeof(vectors[0]),cudaMemcpyHostToDevice);
	one_trajectory();
	cudaFree(vectors);
}
void RungeCUDA::SetTimeStep(const double& in)
{
	dt=in;
}
void RungeCUDA::SetStepsNumber(const unsigned int& in)
{
	Nsteps = in;
}
void RungeCUDA::SetOutputSteps(const unsigned int& in)
{
	Noutputs = in;
}
void RungeCUDA::SetCudaDeviceNumber(const unsigned int& in)
{
	CudaDeviceNumber = in;
}
void RungeCUDA::SetParameters(std::vector<double>& in)
{
	parameters = &in;
}
void RungeCUDA::SetOperator(std::unique_ptr<IOperator>& in)
{
	operator_pointer = &in;
}
void RungeCUDA::SetInitState(std::vector<cuDoubleComplex>& in)
{
	init_state = &in;
}
void RungeCUDA::SetOutputs(std::vector<std::unique_ptr<IOutput> > & in)
{
	outputs = &in;
}

