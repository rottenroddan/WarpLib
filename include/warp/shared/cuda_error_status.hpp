//
// Created by Steven Roddan on 1/27/2026.
//

#ifndef WARPLIB_CUDA_ERROR_STATUS_HPP
#define WARPLIB_CUDA_ERROR_STATUS_HPP

#define WARP_CUDA_ERROR_CHECK(call)                     \
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

#define WARP_CUDA_CHECK_FOR_IMPLICIT_HOST_MEMORY(_ptr)                  \
    do { cudaPointerAttributes attr{};                                  \
        cudaError_t err = cudaPointerGetAttributes(&attr, _ptr);        \
        if (err != cudaSuccess ||                                       \
            (attr.type != cudaMemoryTypeDevice &&                       \
             attr.type != cudaMemoryTypeManaged)) {                     \
            std::cerr << "Pointer must be device or managed memory\n";  \
            std::abort();                                               \
        }                                                               \
    } while (0);


#endif //WARPLIB_CUDA_ERROR_STATUS_HPP