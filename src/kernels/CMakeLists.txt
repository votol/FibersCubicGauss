cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(FibersCubicKernels)

set (SOURCES OperatorKernels.cu
             OperatorKernels.h
             EntanglementKernels.cu
             EntanglementKernels.h
             IntensityKernels.cu
             IntensityKernels.h
             SqueezeKernels.cu
             SqueezeKernels.h)

SET(CUDA_PROPAGATE_HOST_FLAGS OFF)
if(CUDA_VERSION_MAJOR MATCHES 9)
        set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -ccbin /usr/bin/gcc-6 -O3 -gencode arch=compute_$ENV{CUDA_ARCH},code=sm_$ENV{CUDA_ARCH} -Xcompiler -fPIC)
else()
        set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -ccbin /usr/bin/gcc-7 -O3 -gencode arch=compute_$ENV{CUDA_ARCH},code=sm_$ENV{CUDA_ARCH} -Xcompiler -fPIC)
endif()
include_directories (../)
CUDA_ADD_LIBRARY(${PROJECT_NAME} ${SOURCES} STATIC)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
