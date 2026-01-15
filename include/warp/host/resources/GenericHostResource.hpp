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

        template<class T>
        static void deallocate(T* const _ptr) {
            delete[] _ptr;
        }
    };
}

#endif //WARPLIB_GENERICALLOCATOR_HPP
