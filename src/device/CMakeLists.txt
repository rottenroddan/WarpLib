set(WARP_DEVICE_LIB WarpLibDevice)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_ARCHITECTURES 86)

# # # # # # # # # # # #
# Shared(DLL) Library
# # # # # # # # # # # #
add_library(${WARP_DEVICE_LIB} SHARED CudaKernels.cu device_transformers_inst.cu)

find_package(CUDAToolkit REQUIRED)
target_link_libraries(${WARP_DEVICE_LIB} PRIVATE CUDA::cudart)

target_include_directories(${WARP_DEVICE_LIB}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${WARP_DEVICE_LIB} PRIVATE WARP_DEVICE_EXPORTS)

set_target_properties(${WARP_DEVICE_LIB} PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        POSITION_INDEPENDENT_CODE ON
)

target_compile_features(${WARP_DEVICE_LIB} PUBLIC cxx_std_20)

# Define a list of example targets (names only)
get_property(DLL_EXAMPLE_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)

foreach(exe ${DLL_EXAMPLE_TARGETS})
    add_custom_command(TARGET WarpLibDevice POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:WarpLibDevice>
            $<TARGET_FILE_DIR:${exe}>/$<TARGET_FILE_NAME:WarpLibDevice>
            COMMENT "Copying WarpLibDevice.dll to $<TARGET_FILE_DIR:${exe}>"
    )
endforeach()