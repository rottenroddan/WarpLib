//
// Created by steve on 1/15/2026.
//

#include <gtest/gtest.h>
#include <cuda_runtime.h>
#include <warp/host/resources/CudaDeviceResource.hpp>
#include "../Test_Utils/Common.cuh"
#include "../Test_Utils/ValidationKernels.cuh"
#include "warp/host/resources/GenericHostResource.hpp"

TEST(CudaDeviceAllocationTestSuite, HandlesAllocation) {
    constexpr int size = 512;
    const auto _devicePtr = warp::resource::CudaDeviceResource::allocate<int32_t>(size);
    ASSERT_NE(_devicePtr, nullptr);

    dim3 threadBlock(256);
    dim3 grid((size-1)/threadBlock.x + 1);
    warp::test_util::populateIntDataOnIndex<<<grid, threadBlock>>>(_devicePtr, size);
    cudaDeviceSynchronize();

    const auto _hostPtr = warp::resource::GenericHostResource::allocate<int32_t>(size);
    cudaMemcpy(_hostPtr, _devicePtr, size * sizeof(int32_t), cudaMemcpyDeviceToHost);

    for (int32_t i = 0; i < size; ++i) {
        _hostPtr[i] = i;
        ASSERT_EQ(_hostPtr[i], i);
    }
#ifndef WARPLIB_ZERO_MEMORY
    warp::resource::CudaDeviceResource::deallocate(_devicePtr);
    warp::resource::GenericHostResource::deallocate(_hostPtr);
#else
    warp::resource::CudaDeviceResource::deallocate(_devicePtr, size);
    warp::resource::GenericHostResource::deallocate(_hostPtr, size);
#endif
}

TEST(CudaDeviceAllocationTestSuite, HandlesZeroingData) {
    constexpr int size = 512;
    const auto d_ptr = warp::resource::CudaDeviceResource::allocate<int32_t>(size);
    const auto truth_host = warp::resource::GenericHostResource::allocate<int32_t>(size);
    const auto truth_device = warp::resource::CudaDeviceResource::allocate<int32_t>(size);
    memset(truth_host, 0x0, size * sizeof(int32_t));

    cudaMemcpy(truth_device, truth_host, size * sizeof(int32_t), cudaMemcpyHostToDevice);

    // test
    warp::resource::CudaDeviceResource::zero(d_ptr, size);
    ASSERT_TRUE(warp::test_utils::validateArray<int32_t>(truth_device, d_ptr, size));



#ifndef WARPLIB_ZERO_MEMORY
    warp::resource::CudaDeviceResource::deallocate(d_ptr);
    warp::resource::CudaDeviceResource::deallocate(truth_device);
    warp::resource::GenericHostResource::deallocate(truth_host);
#else
    warp::resource::CudaDeviceResource::deallocate(d_ptr, size);
    warp::resource::CudaDeviceResource::deallocate(truth_device, size);
    warp::resource::GenericHostResource::deallocate(truth_host, size);
#endif
}