//
// Created by Steven Roddan on 12/29/2025.
//

#ifndef WARPLIB_GENEREICROWMAJORLAYOUT_HPP
#define WARPLIB_GENEREICROWMAJORLAYOUT_HPP

#include <warp/shared/cuda_attr_expandables.hpp>
#include <warp/shared/layout/MemoryLayout.hpp>


namespace warp::mem::layout {

    class RowMajorLayout {
    public:
        static constexpr bool is_tiled_layout{false};
        static constexpr MemoryLayout memory_major{row_major};

        static constexpr void resize(size_t rows, size_t cols, size_t totalSize, size_t& actualRows, size_t& actualCols, size_t& actualTotalSize ) {
            actualRows = rows;
            actualCols = cols;
            actualTotalSize = totalSize;
        }

        template<typename Index_T = size_t >
        HOST_DEVICE static Index_T index(const size_t i, const size_t j,
                                         const size_t /*rows*/, const size_t cols,
                                         const size_t /*actualRows*/, const size_t /*actualCols*/) {
            return i * cols + j;
        }
    };

}

#endif //WARPLIB_GENEREICROWMAJORLAYOUT_HPP
