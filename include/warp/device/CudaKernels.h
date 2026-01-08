//
// Created by Steven Roddan on 12/21/2025.
//

#ifndef WARPLIB_CUDAKERNELS_CUH
#define WARPLIB_CUDAKERNELS_CUH

#include "device_api.hpp"

namespace warp::device {
    WARP_DEVICE_API void test(float* x);
    WARP_DEVICE_API void test(double* x);
}

#endif //WARPLIB_CUDAKERNELS_CUH
