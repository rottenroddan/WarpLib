//
// Created by Steven Roddan on 1/27/2026.
//

#ifndef WARPLIB_CUDA_ERROR_STATUS_HPP
#define WARPLIB_CUDA_ERROR_STATUS_HPP

#define CUDA_CHECK(call)                                \
    do {                                                \
        cudaError_t err = (call);                       \
        if (err != cudaSuccess) {                       \
            fprintf(stderr,                             \
                    "CUDA error at %s:%d — %s (%d)\n",  \
                    __FILE__, __LINE__,                 \
                    cudaGetErrorString(err), err);      \
            abort();                                    \
        }                                               \
    } while (0)

#endif //WARPLIB_CUDA_ERROR_STATUS_HPP