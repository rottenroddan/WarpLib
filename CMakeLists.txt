# Wide-Architecture Algebra Runtime Platform
cmake_minimum_required(VERSION 3.27)
project(WarpLib CXX CUDA)

set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create bin folder where dlls will lie.
set(WARP_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${WARP_BIN_DIR})

add_subdirectory(src)
add_subdirectory(examples)


