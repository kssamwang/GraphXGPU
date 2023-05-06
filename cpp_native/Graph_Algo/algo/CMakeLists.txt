cmake_minimum_required(VERSION 3.9)
project(Graph_Algo)

set(CMAKE_CXX_STANDARD 14)

IF ((CUDA_VERSION VERSION_GREATER "10.0") OR (CUDA_VERSION VERSION_EQUAL "10.0"))
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -gencode arch=compute_75,code=sm_75")
ENDIF()

IF ((CUDA_VERSION VERSION_GREATER "11.0") OR (CUDA_VERSION VERSION_EQUAL "11.0"))
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -gencode arch=compute_80,code=sm_80")
ENDIF()

add_subdirectory(BellmanFord)
add_subdirectory(LabelPropagation)
add_subdirectory(ConnectedComponent)
#add_subdirectory(StronglyConnectedComponent)
add_subdirectory(DDFS)
add_subdirectory(PageRank)
add_subdirectory(JumpIteration)
