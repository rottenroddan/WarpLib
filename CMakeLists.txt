# Wide-Architecture Algebra Runtime Platform
cmake_minimum_required(VERSION 4.1)

# Force nvcc to allow unsupported MSVC for the compiler ID test
set(CMAKE_CUDA_FLAGS_INIT "--allow-unsupported-compiler")
project(WarpLib CXX CUDA)

set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# create bin folder where dlls will lie.
set(WARP_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${WARP_BIN_DIR})

# GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)


