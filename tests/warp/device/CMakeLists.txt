project(WarpLib_Device_Tests CUDA)
add_executable(WarpLib_Device_Tests
        TestCudaDeviceResource.cu
        Test_Utils/ValidationKernels.cu
)

set_target_properties(WarpLib_Device_Tests PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
)

target_link_libraries(WarpLib_Device_Tests
        PRIVATE
        WarpLibHost
        WarpLibDevice
        GTest::gtest
        GTest::gtest_main
        cuda
)

include(GoogleTest)
gtest_discover_tests(WarpLib_Device_Tests)