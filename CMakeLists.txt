cmake_minimum_required(VERSION 4.1)
project(WarpLib CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output folders
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Fetch GTest
option(WARPLIB_BUILD_TESTS "Build WarpLib tests" ${PROJECT_IS_TOP_LEVEL})
option(WARPLIB_STATIC_ZERO_MEMORY_AFTER_FREE "Build Static WarpLib with default behavior of zeroing memory after freeing" ${PROJECT_IS_TOP_LEVEL})
include(FetchContent)
if(WARPLIB_BUILD_TESTS)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Initialize global property for example targets
get_property(DLL_WARP_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)
if(NOT DLL_WARP_TARGETS)
    set_property(GLOBAL PROPERTY WarpLibDeviceTargets "")
endif()

#function(append_to_device_target target)
#    get_property(DLL_WARP_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)
#    list(APPEND DLL_WARP_TARGETS ${target})
#    set_property(GLOBAL PROPERTY WarpLibDeviceTargets "${DLL_WARP_TARGETS}")
#endfunction()
#
#function(copy_warplib_device exe)
#    add_custom_command(TARGET ${exe} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            $<TARGET_FILE:WarpLibDevice>
#            $<TARGET_FILE_DIR:${exe}>
#            COMMENT "Copying WarpLibDevice.dll next to ${exe}"
#    )
#endfunction()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(WarpLibHelpers.cmake)

# Subdirectories
add_subdirectory(examples)
if(WARPLIB_BUILD_TESTS)
    add_subdirectory(tests)
    enable_testing()
endif()
add_subdirectory(src)
