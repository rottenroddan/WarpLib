//
// Created by Steven Roddan on 12/26/2025.
//

#ifndef WARPLIB_MATRIX_HPP
#define WARPLIB_MATRIX_HPP


#include <concepts>
#include <memory>
#include <type_traits>

#include <warp/shared/layout/MemoryLayout.hpp>
#include <warp/host/resources/GenericHostResource.hpp>
#include "warp/shared/layout/RowMajorLayout.hpp"

namespace warp  {
    /**
     * @concept ResourcePolicy
     *
     * Constrains a type `Resource` to act as a compile-time selectable resource
     * management policy, providing allocation and deallocation for arbitrary types.
     *
     * This concept requires that `Resource` exposes:
     *  - `allocate<T>(size_t)` returning a pointer convertible to `T*`
     *  - `deallocate<T>(T*)` compatible with `allocate`
     *  - `zero<T>(T*, size_t)` performing raw zero-initialization
     *  - `cpu_accessible` as a static boolean indicating CPU accessibility
     *
     * These requirements are checked at compile time, ensuring:
     *  - Allocation and deallocation semantics are valid for any type `T`
     *  - Memory operations are constexpr-friendly where applicable
     *  - CPU-accessible resources can safely provide `at()`-style access
     *
     * Using this concept guarantees that resource selection, allocation,
     * initialization, and deallocation are fully resolved at compile time,
     * enabling aggressive inlining and eliminating runtime dispatch in allocation paths.
     */
    template<typename Resource, typename T>
    concept ResourcePolicy = requires {
        {Resource::template zero<T>(std::declval<T*>(), std::declval<size_t>())} -> std::same_as<void>;
        {Resource::template allocate<T>(size_t{}) } -> std::same_as<T*>;
        {Resource::template deallocate<T>(std::declval<T*>())};
        {Resource::cpu_accessible } -> std::convertible_to<bool>;
    };

    /**
     * @concept LayoutPolicy
     *
     * Constrains a type `T` to provide a compile-time memory layout policy.
     *
     * This concept requires a static `T::getMajor()` member returning a
     * `layout::MemoryMajor` enum value that is not only type-correct, but
     * also a *constant expression* usable in template instantiation.
     *
     * The use of `std::integral_constant<decltype(T::getMajor()), T::getMajor()>`
     * forces the compiler to treat the returned enum value as a non-type
     * template argument. This guarantees that:
     *
     *  - `T::getMajor()` is evaluable at compile time
     *  - the value has external linkage semantics suitable for template use
     *  - layout selection can participate in overload resolution and
     *    specialization without generating runtime branches
     *
     * The explicit enum check prevents accidental use of integral or
     * user-defined proxy types that would weaken compile-time guarantees.
     *
     * In effect, this concept enforces that memory layout decisions are fully
     * resolved during compilation, enabling optimal code generation and
     * eliminating any runtime layout dispatch.
     */
    template<typename Layout, typename T>
    concept LayoutPolicy = requires
        {
            {Layout::is_tiled_layout } -> std::convertible_to<bool>;
        }
        && ((Layout::is_tiled_layout) && (requires {{Layout::tile_size} -> std::convertible_to<size_t>;})
            ||
            ((!Layout::is_tiled_layout) && !(requires {{Layout::tile_size} -> std::convertible_to<size_t>;}))
            )
        && requires {
        {Layout::memory_major} -> std::convertible_to<const mem::MemoryLayout>;
        {Layout::resize(std::declval<size_t>(), // row
                        std::declval<size_t>(), // col
                        std::declval<size_t>(), // totalSize
                        std::declval<size_t&>(), // lvalue ref actualRow
                        std::declval<size_t&>(), // lvalue ref actualCol
                        std::declval<size_t&>()) // lvalue ref actualTotalSize
        } -> std::same_as<void>;
        {Layout::index(std::declval<size_t>(), // row
                        std::declval<size_t>(), // col
                        std::declval<size_t>(), // totalSize
                        std::declval<size_t>(), // lvalue ref actualRow
                        std::declval<size_t>(), // lvalue ref actualCol
                        std::declval<size_t>()) // lvalue ref actualTotalSize
        } -> std::convertible_to<size_t>;
    };

    /**
     *
     * @tparam T
     * @tparam Resource
     * @tparam Layout
     */
    template<typename T,
            typename Resource = resource::GenericHostResource,
            typename Layout = mem::layout::RowMajorLayout>
    requires ResourcePolicy<Resource, T> && LayoutPolicy<Layout, T>
    class Matrix {
        std::shared_ptr<T[]> _matrix;
        size_t rows, cols, totalSize, actualRows{}, actualCols{}, actualTotalSize{};

    public:
        // types
        using value_type = T;
        using resource_type = Resource;
        using layout_type = Layout;


        Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), totalSize(rows * cols) {
            Layout::resize(rows, cols, totalSize, actualRows, actualCols, actualTotalSize);

            auto* _raw = Resource::template allocate<T>(actualTotalSize);
            Resource::template zero<T>(_raw, actualTotalSize);
            _matrix = std::shared_ptr<T[]>(_raw, [=](T* _ptr){ Resource::template deallocate<T>(_ptr); });
        }

        T get(size_t i, size_t j) const requires Resource::cpu_accessible {
            return _matrix[layout_type::index(i, j, rows, cols, actualRows, actualCols)];
        }

        T& at(size_t i, size_t j) requires Resource::cpu_accessible {
            return _matrix[layout_type::index(i, j, rows, cols, actualRows, actualCols)];
        }

        [[nodiscard]] size_t getRows() const {
            return rows;
        }

        [[nodiscard]] size_t getCols() const {
            return cols;
        }

        [[nodiscard]] size_t getTotalSize() const {
            return totalSize;
        }

        [[nodiscard]] size_t getActualRows() const {
            return actualRows;
        }

        [[nodiscard]] size_t getActualCols() const {
            return actualCols;
        }

        [[nodiscard]] size_t getActualTotalSize() const {
            return actualTotalSize;
        }
    };
}

#endif //WARPLIB_MATRIX_HPP
