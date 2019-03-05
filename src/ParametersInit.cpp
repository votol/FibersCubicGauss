#include "ParametersInit.h"
#include "schema.h"
ParametersHolder::ParametersHolder(YAML::Node&& in)
{
    parameters.resize(5);
    parameters[0] = 0.0;
    parameters[1] = in[FibersCubicGaussSchema::PARAMETER_Nfibs].as<double>();
    parameters[2] = in[FibersCubicGaussSchema::PARAMETER_Nfibs_calc].as<double>();
    parameters[3] = in[FibersCubicGaussSchema::PARAMETER_L].as<double>();
    parameters[4] = in[FibersCubicGaussSchema::PARAMETER_alpha].as<double>();
}
