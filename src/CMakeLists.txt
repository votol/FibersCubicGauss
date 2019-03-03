cmake_minimum_required(VERSION 3.0)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set (SOURCES main.cpp
             NetCdfWriter.cpp
             OutputInterface.h
             NetCdfWriter.h
             )

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_custom_command(
    OUTPUT  schema.h
    COMMAND ${PARENT_DIR}/Workflow/scripts/generateSchema.py -d ${PARENT_DIR}/description.yaml -f ${CMAKE_CURRENT_BINARY_DIR}/schema.h
    DEPENDS ${PARENT_DIR}/description.yaml
)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (~/include)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/schema.h
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries (${PROJECT_NAME} ~/lib/libyaml-cpp.so
                                        netcdf_c++4)



