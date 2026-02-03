//
// Created by steve on 1/20/2026.
//

#ifndef WARPLIB_PINNEDMEMORYRESOURCE_HPP
#define WARPLIB_PINNEDMEMORYRESOURCE_HPP
#include <cuda_runtime.h>

namespace warp::mem::resource {
    class CudaPinnedResource {
    public:
        static constexpr bool cpu_accessible{true};

        template<class T>
        static T* allocate(const size_t size) {
            T* _ptr = nullptr;
            cudaMallocHost(&_ptr, size * sizeof(T));
            return _ptr;
        }

        template<class T>
        static void zero(T* const _dst, const size_t size) {
            cudaMemset(_dst, 0x0, size * sizeof(T));
        }


        template<class T>
        static void deallocate(T* const _ptr, const size_t size) {
#ifdef WARPLIB_ZERO_MEMORY
            cudaMemset(static_cast<void *>(_ptr), 0x0, size * sizeof(T));
#endif
            cudaFreeHost(static_cast<void *>(_ptr));
        }
    };
}

#endif //WARPLIB_PINNEDMEMORYRESOURCE_HPP