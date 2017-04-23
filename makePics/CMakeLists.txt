cmake_minimum_required(VERSION 2.8)
set(CUDA_HOST_COMPILER /usr/bin/gcc-5)
list( APPEND CUDA_NVCC_FLAGS "-std=c++11 ${CUDA_NVCC_FLAGS}")
project ( makepics )
find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -O3 -Wno-deprecated-gpu-targets)

cuda_add_executable(makepics makepics.cu)

target_link_libraries(
    makepics ${OpenCV_LIBS} -lm
)
