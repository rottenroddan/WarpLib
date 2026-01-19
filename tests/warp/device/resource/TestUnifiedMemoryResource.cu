//
// Created by steve on 1/19/2026.
//

//
// Created by steve on 1/15/2026.
//

#include <gtest/gtest.h>
#include <cuda_runtime.h>
#include <warp/host/resources/UnifiedMemoryResource.hpp>
#include "../Test_Utils/ValidationKernels.cuh"
#include "../Test_Utils/Common.cuh"
#include "warp/host/resources/CudaDeviceResource.hpp"
#include "warp/host/resources/GenericHostResource.hpp"



TEST(UnifiedMemoryResourceTestSuite, HandlesAllocation) {
    constexpr int size = 512;
    const auto _unifiedPtr = warp::resource::UnifiedMemoryResource::allocate<int32_t>(size);
    ASSERT_NE(_unifiedPtr, nullptr);

    dim3 threadBlock(256);
    dim3 grid((size-1)/threadBlock.x + 1);
    warp::test_util::populateIntDataOnIndex<<<grid, threadBlock>>>(_unifiedPtr, size);
    cudaDeviceSynchronize();

    for (int32_t i = 0; i < size; ++i) {
        _unifiedPtr[i] = i;
        ASSERT_EQ(_unifiedPtr[i], i);
    }
    warp::resource::UnifiedMemoryResource::deallocate(_unifiedPtr);
}

TEST(UnifiedMemoryResourceTestSuite, HandlesZeroingData) {
    constexpr int size = 512;
    const auto u_ptr = warp::resource::UnifiedMemoryResource::allocate<int32_t>(size);
    const auto truth_host = warp::resource::GenericHostResource::allocate<int32_t>(size);
    const auto truth_device = warp::resource::CudaDeviceResource::allocate<int32_t>(size);
    memset(truth_host, 0x0, size * sizeof(int32_t));

    cudaMemcpy(truth_device, truth_host, size * sizeof(int32_t), cudaMemcpyHostToDevice);

    // test
    warp::resource::UnifiedMemoryResource::zero(u_ptr, size);
    ASSERT_TRUE(warp::test_utils::validateArray<int32_t>(truth_device, u_ptr, size));

    warp::resource::UnifiedMemoryResource::deallocate(u_ptr);
    warp::resource::CudaDeviceResource::deallocate(truth_device);
    warp::resource::GenericHostResource::deallocate(truth_host);
}