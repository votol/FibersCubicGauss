#include "ParametersInit.h"
ParametersHolder::ParametersHolder(YAML::Node&& in)
{
    parameters.resize(5);
    parameters[0] = 0.0;
    parameters[1] = in["width"].as<double>();
    parameters[2] = in["width_calc"].as<double>();
    parameters[3] = in["g"].as<double>();
    parameters[4] = in["D"].as<double>();
}
