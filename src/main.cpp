#include <iostream>
#include "yaml-cpp/yaml.h"
#include "schema.h"
#include "NetCdfWriter.h"

int main(int argc, char **argv)
{
    YAML::Node config = YAML::LoadFile(argv[1]);
    std::string output_dir = config["properties"]
								  [FibersCubicGaussSchema::PROPERTY_output_path].as<std::string>();
    std::vector<std::unique_ptr<IOutput> > outputs(0);
    NetCdfWriter netcdf_writer_instance(
			output_dir + "/output.nc", outputs, 0);
    return 0;
}
