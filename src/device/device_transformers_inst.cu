//
// Created by Steven Roddan on 1/28/2026.
//

#include "device_transformers.cu"

namespace warp::transformers::kernels {
    template WARP_DEVICE_API void launchCopyCastDataOnCudaKernel(int*, float*, size_t, bool);
    template WARP_DEVICE_API void launchCopyCastDataOnCudaKernel(float*, int*, size_t, bool);
}