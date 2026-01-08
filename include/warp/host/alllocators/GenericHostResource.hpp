//
// Created by Steven Roddan on 12/27/2025.
//

#ifndef WARPLIB_GENERICALLOCATOR_HPP
#define WARPLIB_GENERICALLOCATOR_HPP

#include <warp/host/alllocators/MemorySpace.hpp>

namespace warp::resource {
    class GenericHostResource {
    public:
        static constexpr bool cpu_accessible{true};

        template<class T>
        static T* allocate(size_t size) {
            return new T[size];
        }

        template<class T>
        static void zero(T* _dst, size_t size) {
            memset((void*)_dst, 0x0, size * sizeof(T));
        }

        template<class T>
        static void deallocate(T* _ptr) {
            delete[] _ptr;
        }
    };
}

#endif //WARPLIB_GENERICALLOCATOR_HPP
