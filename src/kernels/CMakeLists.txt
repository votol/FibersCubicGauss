cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(FibersCubicKernels)

set (SOURCES OperatorKernels.cu
			 EntanglementKernels.cu
             IntensityKernels.cu)

SET(CUDA_PROPAGATE_HOST_FLAGS OFF)
if(CUDA_VERSION_MAJOR MATCHES 5)
	set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -ccbin /usr/local/bin/g++4.6.4 -O3 -gencode arch=compute_$ENV{CUDA_ARCH},code=sm_$ENV{CUDA_ARCH})
else()
	set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -ccbin /usr/bin/gcc-5 -O3 -gencode arch=compute_$ENV{CUDA_ARCH},code=sm_$ENV{CUDA_ARCH} -Xcompiler -fPIC)
endif()
include_directories (../)
CUDA_ADD_LIBRARY(${PROJECT_NAME} ${SOURCES} STATIC)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
