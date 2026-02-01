//
// Created by Steven Roddan on 1/27/2026.
//

#ifndef WARPLIB_TRANSFORMERKERNELS_CUH
#define WARPLIB_TRANSFORMERKERNELS_CUH

#include <cuda_runtime.h>
#include <warp/device/device_api.hpp>
#include <warp/shared/cuda_error_status.hpp>

#define WARP_CUDA_DEFAULT_THREAD_COUNT 256

namespace warp::transformers::kernels {
    // template<typename T, typename U>
    //  __global__ void _castArrayKernelRestrict(T* __restrict__ dst, const U* __restrict__ src, size_t size);
    //
    // template<typename T, typename U>
    // __global__ void _castArrayKernel(T* dst, const U* src, size_t size);

    template<typename T, typename U>
    WARP_DEVICE_API void launchCastDataOnCudaKernel(T*dst, U*src, size_t size, bool restrictPtrs);
}

#endif //WARPLIB_TRANSFORMERKERNELS_CUH