//
// Created by Steven Roddan on 12/27/2025.
//

#ifndef WARPLIB_GENERICALLOCATOR_HPP
#define WARPLIB_GENERICALLOCATOR_HPP

namespace warp::resource {
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

#ifndef WARPLIB_ZERO_MEMORY
        template<class T>
        static void deallocate(T* const _ptr) {
            delete[] _ptr;
        }
#else
        template<class T>
        static void deallocate(T* const _ptr, const size_t size) {
            memset(_ptr, 0x0, size * sizeof(T));
            delete[] _ptr;
        }
#endif

    };
}

#endif //WARPLIB_GENERICALLOCATOR_HPP
