#include <iostream>
#include <cuda_runtime.h>
#include <string>
#include "ParametersInit.h"
#include "RungeCUDA.h"
#include "Operator.h"
#include "yaml-cpp/yaml.h"
#include "NetCdfWriter.h"
#include "OutputIntensity.h"
#include "ParameterDefines.h"
#include "schema.h"

unsigned int GetDim_main(const std::vector<double>& parameters)
{
    return 1+(unsigned int)(Nfibs) * 3 + 2 * (unsigned int)(Nfibs) * (unsigned int)(Nfibs);
}

void make_init(std::vector<double>& vec, const std::vector<double>& parameters)
{
    unsigned int fib_num = 1 + (unsigned int)Nfibs - ((unsigned int)Nfibs)%2;
    vec[fib_num] = alpha;
    vec[0] = 1.0;
}

int main(int argc, char **argv)
{
    YAML::Node config = YAML::LoadFile(argv[1]);
    std::string output_dir = config["properties"]
                     [FibersCubicGaussSchema::PROPERTY_output_path].as<std::string>();

    cudaSetDevice(config["properties"][FibersCubicGaussSchema::PROPERTY_cuda_device].as<unsigned int>());
    ParametersHolder parameters_holder_instance(config["parameters"]);

    unsigned int DIM = GetDim_main(parameters_holder_instance.GetParameters());
    std::vector<double> init_state(DIM, 0.0);

    make_init(init_state, parameters_holder_instance.GetParameters());
    std::unique_ptr<IOperator> operator_pointer(
                new OperatorBase(parameters_holder_instance.GetParameters(), DIM));

    OutputIntensity oIntensity(FibersCubicGaussSchema::OUTPUT_I, parameters_holder_instance.GetParameters(),
                               config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    std::list<IOutputCalculator* > outputs;
    outputs.push_back(&oIntensity);

    RungeCUDA runge_cuda_istatnce;
    runge_cuda_istatnce.SetCudaDeviceNumber(
           config["properties"][FibersCubicGaussSchema::PROPERTY_cuda_device].as<unsigned int>());
    runge_cuda_istatnce.SetInitState(init_state);
    runge_cuda_istatnce.SetOperator(operator_pointer);
    runge_cuda_istatnce.SetOutputs(outputs);
    runge_cuda_istatnce.SetDimension(DIM);
    runge_cuda_istatnce.SetOutputSteps(config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    runge_cuda_istatnce.SetParameters(parameters_holder_instance.GetParameters());
    runge_cuda_istatnce.SetStepsNumber(config["parameters"][FibersCubicGaussSchema::PARAMETER_Nsteps].as<unsigned int>());
    runge_cuda_istatnce.SetTimeStep(config["parameters"][FibersCubicGaussSchema::PARAMETER_dt].as<double>());
    runge_cuda_istatnce.Calculate();

    std::list<IOutput* > outputsNCDF;
    outputsNCDF.push_back(&oIntensity);
    NetCdfWriter netcdf_writer_instance(
            output_dir + "/output.nc", outputsNCDF,
            config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    return 0;
}
