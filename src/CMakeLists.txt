cmake_minimum_required(VERSION 3.0)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set (SOURCES main.cpp
             NetCdfWriter.cpp
             NetCdfWriter.h
             Operator.cpp
             Operator.h
             OperatorElement.h
             OperatorInterface.h
             OutputCaclulatorInterface.h
             OutputEntanglement.cpp
             OutputEntanglement.h
             OutputTime.cpp
             OutputTime.h
             OutputMean.cpp
             OutputMean.h
             OutputIntensity.cpp
             OutputIntensity.h
             OutputSqueeze.cpp
             OutputSqueeze.h
             OutputInterface.h
             ParameterDefines.h
             ParametersInit.cpp
             ParametersInit.h
             RungeCUDA.cpp
             RungeCUDA.h
             Indexes.h
             complex.h
             )

find_package (CUDA REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(TAR ${PROJECT_NAME}_c++)

add_custom_command(
    OUTPUT  schema.h
    COMMAND ${PARENT_DIR}/Workflow/scripts/generateSchema.py -d ${PARENT_DIR}/description.yaml -f ${CMAKE_CURRENT_BINARY_DIR}/schema.h
    DEPENDS ${PARENT_DIR}/description.yaml
)
add_custom_command(
        OUTPUT ${EXECUTABLE_OUTPUT_PATH}/CalcProj
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/src/CalcProj
                ${EXECUTABLE_OUTPUT_PATH}/CalcProj
        DEPENDS ${CMAKE_SOURCE_DIR}/src/CalcProj
        )


get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (${CUDA_INCLUDE_DIRS})
include_directories (./kernels)
include_directories (./)
include_directories (~/include)

add_executable(${TAR}
    ${SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/schema.h
    ${EXECUTABLE_OUTPUT_PATH}/CalcProj
)


CUDA_ADD_CUBLAS_TO_TARGET(${TAR})
set_property(TARGET ${TAR} PROPERTY CXX_STANDARD 11)
add_subdirectory(kernels)
target_link_libraries (${TAR} ~/lib/libyaml-cpp.so
                                        netcdf_c++4
                                        FibersCubicKernels
                                        ${CUDA_LIBRARIES})



