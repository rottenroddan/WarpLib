//
// Created by steve on 1/16/2026.
//

#ifndef WARPLIB_UNIFIEDMEMORYRESOURCE_HPP
#define WARPLIB_UNIFIEDMEMORYRESOURCE_HPP

#include <cuda_runtime.h>

namespace warp::mem::resource {
    class CudaManagedResource {
    public:
        static constexpr bool cpu_accessible{true};

        template<class T>
        static T* allocate(const size_t size) {
            T* _ptr;
            cudaMallocManaged(&_ptr, size * sizeof(T));
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
            cudaFree(static_cast<void *>(_ptr));
        }
    };
}

#endif //WARPLIB_UNIFIEDMEMORYRESOURCE_HPP