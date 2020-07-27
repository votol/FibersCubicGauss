#include <fstream> 
#include <iostream>
#include <cuda_runtime.h>
#include <string>
#include "ParametersInit.h"
#include "RungeCUDA.h"
#include "Operator.h"
#include "yaml-cpp/yaml.h"
#include "NetCdfWriter.h"
#include "OutputTime.h"
#include "OutputIntensity.h"
#include "OutputMean.h"
#include "OutputEntanglement.h"
#include "OutputSqueeze.h"
#include "ParameterDefines.h"
#include "schema.h"

#include "Indexes.h"
#include "ParameterDefines.h"
unsigned int GetDim_main(const std::vector<double>& parameters)
{
    return 1+(unsigned int)(Nfibs) * 3 + 2 * (unsigned int)(Nfibs) * (unsigned int)(Nfibs);
}

void make_init(std::vector<double>& vec, const std::vector<double>& parameters, std::string& path)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    std::ifstream ifs;
    double tmpd;
    
    ifs.open (path + "/init.bin", std::ifstream::in | std::ifstream::binary);
    
    for (unsigned int ind = 0; ind < (unsigned int)Nfibs; ind ++){
        ifs.read((char *)&tmpd, 8);
        vec[1 + ind *2] = tmpd;
        //vec[1 + ind *2] = 0.0;
        vec[2 + ind *2] = 0.0;
    }
    
    //vec[DI_r(0,0)] = 100.0;
    vec[0] = 1.0;
    ifs.close();
}

int main(int argc, char **argv)
{
    YAML::Node config = YAML::LoadFile(argv[1]);
    std::string output_dir = config["properties"]
                     [FibersCubicGaussSchema::PROPERTY_output_path].as<std::string>();

    std::string tmp_dir = config["properties"]
                     [FibersCubicGaussSchema::PROPERTY_tmp_path].as<std::string>();
    
    cudaSetDevice(config["properties"][FibersCubicGaussSchema::PROPERTY_cuda_device].as<unsigned int>());
    ParametersHolder parameters_holder_instance(config["parameters"]);

    unsigned int DIM = GetDim_main(parameters_holder_instance.GetParameters());
    std::vector<double> init_state(DIM, 0.0);

    make_init(init_state, parameters_holder_instance.GetParameters(), tmp_dir);
    std::unique_ptr<IOperator> operator_pointer(
                new OperatorBase(parameters_holder_instance.GetParameters(), DIM));

    
    OutputTime ot(FibersCubicGaussSchema::OUTPUT_time, parameters_holder_instance.GetParameters(),
                               config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    OutputIntensity oIntensity(FibersCubicGaussSchema::OUTPUT_I, parameters_holder_instance.GetParameters(),
                               config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    OutputSqueeze oSq(FibersCubicGaussSchema::OUTPUT_Sq, parameters_holder_instance.GetParameters(),
                               config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    OutputEntanglement oEN(FibersCubicGaussSchema::OUTPUT_EN, parameters_holder_instance.GetParameters(),
                               config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    OutputMean oa2(FibersCubicGaussSchema::OUTPUT_a2, parameters_holder_instance.GetParameters(),
                               config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    std::list<IOutputCalculator* > outputs;
    outputs.push_back(&ot);
    outputs.push_back(&oIntensity);
    outputs.push_back(&oEN);
    outputs.push_back(&oSq);
    outputs.push_back(&oa2);

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
    outputsNCDF.push_back(&ot);
    outputsNCDF.push_back(&oIntensity);
    outputsNCDF.push_back(&oEN);
    outputsNCDF.push_back(&oSq);
    outputsNCDF.push_back(&oa2);
    NetCdfWriter netcdf_writer_instance(
            output_dir + "/output.nc", outputsNCDF,
            config["parameters"][FibersCubicGaussSchema::PARAMETER_Nout].as<unsigned int>());
    return 0;
}
