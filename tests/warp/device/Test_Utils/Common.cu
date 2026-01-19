//
// Created by steve on 1/19/2026.
//

#include "Common.cuh"

namespace warp::test_util {
    __global__ void populateIntDataOnIndex(int32_t* _ptr, int size) {
        if (const unsigned int index = blockIdx.x * blockDim.x + threadIdx.x; index < size) {
            _ptr[index] = index;
        }
    }
}