//
// Created by Steven Roddan on 12/27/2025.
//

#ifndef WARPLIB_GENERICALLOCATOR_HPP
#define WARPLIB_GENERICALLOCATOR_HPP

#include <Windows.h>

namespace warp::mem::resource {
    class GenericHostResource {
    public:
        static constexpr bool cpu_accessible{true};

        template<class T>
        static T* allocate(const size_t size) {
            return new T[size];
        }

        template<class T>
        static void zero(T* const _dst, const size_t size) {
            memset(_dst, T{0}, size * sizeof(T));
        }

        template<class T>
        static void deallocate(T* const _ptr, const size_t size) {
#ifdef WIN32
#ifdef WARPLIB_ZERO_MEMORY
            SecureZeroMemory(_ptr, size * sizeof(T));
#endif
#endif
            delete[] _ptr;
        }
    };
}

#endif //WARPLIB_GENERICALLOCATOR_HPP
