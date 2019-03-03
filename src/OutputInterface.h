#ifndef __OutputInterface_h_
#define __OutputInterface_h_
#include <string>
#include <vector>


class IOutput
{
public:
	IOutput(){};
	virtual ~IOutput(){};
	virtual const std::string& GetName() = 0;
	virtual const std::vector<double>& GetData() = 0;
	virtual const std::vector<size_t>& GetDimensions() = 0;
};

#endif /*__OutputInterface_h_*/
