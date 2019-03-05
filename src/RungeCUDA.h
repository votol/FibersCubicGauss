#ifndef __QJumps_h_
#define __QJumps_h_
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <vector>
#include <list>
#include <memory>
#include <chrono>
#include <string>
#include "OperatorInterface.h"
#include "OutputCaclulatorInterface.h"


class RungeCUDA
{
	double dt;
	unsigned int Nsteps;
	unsigned int Noutputs;
	unsigned int Nrelaxations;

	unsigned int CudaDeviceNumber;
	cublasHandle_t blas_handle;

	std::vector<double>* parameters;
	std::unique_ptr<IOperator>* operator_pointer;
    std::vector<double>* init_state;
    std::list<IOutputCalculator*>* outputs;

    double* vectors;

	double output_coe;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::high_resolution_clock::time_point t1;

	std::string file_uuid;

	unsigned int DIM;

	int Get_temperature(void);
	int interruption(void);

	void one_trajectory(void);
public:
	RungeCUDA();
	~RungeCUDA();
	void Calculate(void);
    void SetDimension(const unsigned int& in);
    void SetTimeStep(const double&);
	void SetStepsNumber(const unsigned int&);
	void SetOutputSteps(const unsigned int&);
	void SetCudaDeviceNumber(const unsigned int&);
	void SetParameters(std::vector<double>&);
	void SetOperator(std::unique_ptr<IOperator>&);
    void SetInitState(std::vector<double>&);
    void SetOutputs(std::list<IOutputCalculator*> &);
};


#endif /*__QJumps_h_*/
