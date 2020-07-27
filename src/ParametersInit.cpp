#include "ParametersInit.h"
#include "schema.h"
#include "ParameterDefines.h"
#include <iostream>
ParametersHolder::ParametersHolder(YAML::Node&& in)
{
    parameters.resize(6);
    t = 0.0;
    Nfibs = in[FibersCubicGaussSchema::PARAMETER_Nfibs].as<double>();
    Nfibs_calc = in[FibersCubicGaussSchema::PARAMETER_Nfibs_calc].as<double>();
    L = in[FibersCubicGaussSchema::PARAMETER_L].as<double>();
    gamma = in[FibersCubicGaussSchema::PARAMETER_gamma].as<double>();
    G = in[FibersCubicGaussSchema::PARAMETER_G].as<double>();
}
