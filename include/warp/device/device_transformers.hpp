//
// Created by Steven Roddan on 1/27/2026.
//

#ifndef WARPLIB_TRANSFORMERKERNELS_CUH
#define WARPLIB_TRANSFORMERKERNELS_CUH

#include <cuda_runtime.h>
#include <iostream>
#include <ostream>

#include <warp/device/device_api.hpp>
#include <warp/shared/cuda_error_status.hpp>
#include <warp/shared/float_types.hpp>

#define WARP_CUDA_DEFAULT_THREAD_COUNT 256

namespace warp::transformers::kernels {
    template<typename DstType, typename SrcType>
    WARP_DEVICE_API void launchCopyCastDataOnCudaKernel(DstType* dst, SrcType* src, size_t size, bool restrictPtrs);

    template<typename DstType, typename SrcType, typename DstLayout, typename SrcLayout>
    WARP_DEVICE_API void launchCopyOnCudaKernel(DstType* dst, SrcType* src, size_t rows, size_t cols,
                                                size_t actualRows, size_t actualCols, size_t tileSize);
}

#endif //WARPLIB_TRANSFORMERKERNELS_CUH