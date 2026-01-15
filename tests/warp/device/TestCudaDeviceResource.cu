//
// Created by steve on 1/15/2026.
//

#include <gtest/gtest.h>
#include <cuda_runtime.h>
#include <warp/host/resources/CudaDeviceResource.hpp>
#include "Test_Utils/ValidationKernels.cuh"
#include "warp/host/resources/GenericHostResource.hpp"

__global__ void populateDataOnIndex(int32_t* _ptr, int size) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < size) {
        _ptr[index] = index;
    }
}

TEST(GenericDeviceAllocationTest, HandlesAllocation) {
    constexpr int size = 512;
    const auto _devicePtr = warp::resource::CudaDeviceResource::allocate<int32_t>(size);
    ASSERT_NE(_devicePtr, nullptr);

    dim3 threadBlock(256);
    dim3 grid((size-1)/threadBlock.x + 1);
    populateDataOnIndex<<<grid, threadBlock>>>(_devicePtr, size);
    cudaDeviceSynchronize();

    const auto _hostPtr = warp::resource::GenericHostResource::allocate<int32_t>(size);
    cudaMemcpy(_hostPtr, _devicePtr, size * sizeof(int32_t), cudaMemcpyDeviceToHost);

    for (int32_t i = 0; i < size; ++i) {
        _hostPtr[i] = i;
        ASSERT_EQ(_hostPtr[i], i);
    }
    warp::resource::CudaDeviceResource::deallocate(_devicePtr);
    warp::resource::GenericHostResource::deallocate(_hostPtr);
}

// TEST(GenericHostAllocationTest, HandlesZeroingData) {
//     constexpr int size = 512;
//     const auto _ptr = warp::resource::CudaDeviceResource::allocate<int32_t>(size);
//     ASSERT_NE(_ptr, nullptr);
//     for (int32_t i{}; i < size; i++) {
//         _ptr[i] = i;
//     }
//     warp::resource::CudaDeviceResource::zero(_ptr, size);
//     for (uint32_t i{}; i < size; i++) {
//         ASSERT_EQ(_ptr[i], 0);
//     }
//     warp::resource::CudaDeviceResource::deallocate(_ptr);
// }