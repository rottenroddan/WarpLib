//
// Created by Steven Roddan on 12/26/2025.
//

#ifndef WARPLIB_MATRIX_HPP
#define WARPLIB_MATRIX_HPP

#include <concepts>
#include <memory>
#include <type_traits>

#include <warp/host/policies.hpp>
#include <warp/host/resources/GenericHostResource.hpp>
#include <warp/shared/detail.hpp>
#include <warp/shared/layout/MemoryLayout.hpp>
#include <warp/shared/layout/RowMajorLayout.hpp>

#include "Transformers.hpp"

namespace warp  {
    /**
     *
     * @tparam T
     * @tparam Resource
     * @tparam Layout
     */
    template<typename T,
            typename Resource = mem::resource::GenericHostResource,
            typename Layout = mem::layout::RowMajorLayout>
    requires internal::policies::ResourcePolicy<Resource, T> && internal::policies::LayoutPolicy<Layout, T>
    class Matrix {
        std::shared_ptr<T[]> _matrix;
        size_t rows, cols, totalSize, actualRows{}, actualCols{}, actualTotalSize{};

    public:
        // types
        using value_type = T;
        using resource_type = Resource;
        using layout_type = Layout;

        ~Matrix() = default;

        Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), totalSize(rows * cols) {
            Layout::resize(rows, cols, totalSize, actualRows, actualCols, actualTotalSize);

            auto* _raw = Resource::template allocate<T>(actualTotalSize);
            Resource::template zero<T>(_raw, actualTotalSize);
            _matrix = std::shared_ptr<T[]>(_raw, [this](T* _ptr) {
                Resource::template deallocate<T>(_ptr, actualTotalSize);
            });
        }

        template<typename DstMatrix>
        void copyTo(DstMatrix& dst) {
            using transformers::copy;
            copy(dst, *this, detail::internal::priority_2{});
        }

        T* getRaw() const {
            return _matrix.get();
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
