//
// Created by steve on 1/19/2026.
//

#ifndef WARPLIB_HOSTCACHEALIGNEDRESOURCE_HPP
#define WARPLIB_HOSTCACHEALIGNEDRESOURCE_HPP

#include <stdlib.h>
#include <new>

namespace warp::resource {
    class GenericHostResource {
    public:
        static constexpr bool cpu_accessible{true};

        template<class T>
        static T* allocate(const size_t size) {
            return _aligned_malloc(sizeof(T) * size, std::hardware_destructive_interference_size);
        }

        template<class T>
        static void zero(T* const _dst, const size_t size) {
            memset(_dst, T{0}, size * sizeof(T));
        }

        template<class T>
        static void deallocate(T* const _ptr) {
            _aligned_free(_ptr);
        }
    };
}


#endif //WARPLIB_HOSTCACHEALIGNEDRESOURCE_HPP