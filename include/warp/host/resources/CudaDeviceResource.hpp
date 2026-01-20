//
// Created by steve on 1/12/2026.
//

#ifndef WARPLIB_GENERICCUDARESOURCE_HPP
#define WARPLIB_GENERICCUDARESOURCE_HPP

#include <cuda_runtime.h>

namespace warp::resource {
    class CudaDeviceResource {
    public:
        static constexpr bool cpu_accessible{false};

        template<class T>
        static T* allocate(const size_t size) {
            T* _ptr = nullptr;
            cudaMalloc(&_ptr, size * sizeof(T));
            return _ptr;
        }

        template<class T>
        static void zero(T* const _dst, const size_t size) {
            cudaMemset(_dst, 0x0, size * sizeof(T));
        }

#ifndef WARPLIB_ZERO_MEMORY
        template<class T>
        static void deallocate(T* const _ptr) {
            cudaFree(static_cast<void *>(_ptr));
        }
#else
        template<class T>
        static void deallocate(T* const _ptr, const size_t size) {
            cudaMemset(static_cast<void *>(_ptr), 0x0, size * sizeof(T));
            cudaFree(static_cast<void *>(_ptr));
        }
#endif

    };
}

#endif //WARPLIB_GENERICCUDARESOURCE_HPP