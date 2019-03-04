#ifndef __ParametersInit_h_
#define __ParametersInit_h_
#include <vector>
#include "yaml-cpp/yaml.h"

class ParametersHolder
{
	std::vector<double> parameters;
public:
	ParametersHolder(YAML::Node&&);
	~ParametersHolder(){};
	std::vector<double>& GetParameters(){return parameters;};
};


#endif /*__ParametersInit_h_*/
