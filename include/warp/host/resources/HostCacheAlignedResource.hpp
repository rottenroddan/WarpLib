//
// Created by steve on 1/19/2026.
//

#ifndef WARPLIB_HOSTCACHEALIGNEDRESOURCE_HPP
#define WARPLIB_HOSTCACHEALIGNEDRESOURCE_HPP

#include <cstdlib>
#include <new>
#include <Windows.h>

namespace warp::mem::resource {
    class HostCacheAlignedResource {
    public:
        static constexpr bool cpu_accessible{true};

        template<class T>
        static T* allocate(const size_t size) {
            return static_cast<T*>(_aligned_malloc(sizeof(T) * size, std::hardware_destructive_interference_size));
        }

        template<class T>
        static void zero(T* const _dst, const size_t size) {
            memset(_dst, T{0}, size * sizeof(T));
        }

#ifndef WARPLIB_ZERO_MEMORY
        template<class T>
        static void deallocate(T* const _ptr) {
            _aligned_free(_ptr);
        }
#else
        template<class T>
        static void deallocate(T* const _ptr, const size_t size) {
#ifdef WIN32
            SecureZeroMemory(_ptr, size * sizeof(T));
#endif
            _aligned_free(_ptr);
        }
#endif
    };

}


#endif //WARPLIB_HOSTCACHEALIGNEDRESOURCE_HPP