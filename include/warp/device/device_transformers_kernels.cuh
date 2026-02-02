//
// Created by steve on 2/1/2026.
//

#ifndef WARPLIB_DEVICE_TRANSFORMERS_KERNELS_CUH
#define WARPLIB_DEVICE_TRANSFORMERS_KERNELS_CUH

#include <cuda_runtime.h>

namespace warp::transformers::kernels {
    template<typename T, typename U>
    __global__ void _castArrayKernelRestrict(T* __restrict__ dst, const U* __restrict__ src, const size_t size) {
        for (size_t i = blockDim.x * blockIdx.x + threadIdx.x; i < size; i+= blockDim.x * gridDim.x) {
            dst[i] = static_cast<T>(src[i]);
        }
    }

    template<typename T, typename U>
    __global__ void _castArrayKernel(T* dst, const U* src, const size_t size) {
        for (size_t i = blockDim.x * blockIdx.x + threadIdx.x; i < size; i+= blockDim.x * gridDim.x) {
            dst[i] = static_cast<T>(src[i]);
        }
    }
}

#endif //WARPLIB_DEVICE_TRANSFORMERS_KERNELS_CUH