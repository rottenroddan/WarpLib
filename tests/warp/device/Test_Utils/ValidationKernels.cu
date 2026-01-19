//
// Created by steve on 1/15/2026.
//

#include "ValidationKernels.cuh"

template bool warp::test_utils::validateArray(int32_t*, int32_t*, int);
template bool warp::test_utils::validateArray<float>(float*, float*, int);