//
// Created by Steven Roddan on 1/28/2026.
//

#include <warp/shared/layout/RowMajorLayout.hpp>
#include <warp/shared/layout/TileRowMajorLayout.hpp>
#include "device_transformers.cu"

namespace warp::transformers::kernels {
    template WARP_DEVICE_API void launchCopyOnCudaKernel<int, int, mem::layout::RowMajorLayout, mem::layout::TileRowMajorLayout<16>>(int*, int*, size_t, size_t, size_t, size_t, size_t);
    template WARP_DEVICE_API void launchCopyOnCudaKernel<int, int, mem::layout::TileRowMajorLayout<16>, mem::layout::RowMajorLayout>(int*, int*, size_t, size_t, size_t, size_t, size_t);


    template WARP_DEVICE_API void launchCopyCastDataOnCudaKernel(int*, float*, size_t, bool);
    template WARP_DEVICE_API void launchCopyCastDataOnCudaKernel(float*, int*, size_t, bool);
}