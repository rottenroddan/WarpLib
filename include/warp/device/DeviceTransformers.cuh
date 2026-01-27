//
// Created by Steven Roddan on 1/27/2026.
//

#ifndef WARPLIB_TRANSFORMERKERNELS_CUH
#define WARPLIB_TRANSFORMERKERNELS_CUH

#include "device_api.hpp"

namespace warp::transformers::kernels {
    template<typename T, typename U>
    WARP_DEVICE_API void launchCastOnKernelFromAToB(T* const dst, U* const src, const size_t size);
}

#endif //WARPLIB_TRANSFORMERKERNELS_CUH