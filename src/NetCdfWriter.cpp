#include <netcdf>
#include "NetCdfWriter.h"

using namespace netCDF;
using namespace netCDF::exceptions;

NetCdfWriter::NetCdfWriter(const std::string & n, std::vector<std::unique_ptr<IOutput> >& outs, const unsigned int& Tsteps)
{
	NcFile NcFile_instatnce(n, NcFile::replace);
	NcDim timeDim = NcFile_instatnce.addDim("time", Tsteps);
	for(auto it = outs.begin(); it != outs.end(); ++it)
	{
		const std::vector<size_t>& dims = (*it)->GetDimensions();
		if(dims[0] == 1)
		{
			NcVar  var = NcFile_instatnce.addVar((*it)->GetName(), ncDouble, timeDim);
			var.putVar((*it)->GetData().data());
		}
		else
		{
			std::vector<NcDim> NcDims;
			NcDims.push_back(timeDim);
			for(unsigned int peri=0;peri<dims.size();++peri)
			{
				NcDims.push_back(NcFile_instatnce.addDim((*it)->GetName() + "_dim" + std::to_string(peri), dims[peri]));
			}
			NcVar  var = NcFile_instatnce.addVar((*it)->GetName(), ncDouble, NcDims);
			var.putVar((*it)->GetData().data());
		}
	}
}
