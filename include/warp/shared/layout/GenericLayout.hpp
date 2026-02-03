//
// Created by Steven Roddan on 1/12/2026.
//

#ifndef WARPLIB_GENERICLAYOUT_HPP
#define WARPLIB_GENERICLAYOUT_HPP

#include <warp/shared/layout/MemoryLayout.hpp>
#include <warp/shared/cuda_attr_expandables.hpp>

namespace warp::mem::layout {

    template<MemoryLayout mem_type = row_major>
    class GenericLayout {
    public:
        static constexpr bool is_tiled_layout{false};
        static constexpr MemoryLayout memory_major{mem_type};

        static constexpr void resize(const size_t rows, const size_t cols, const size_t totalSize, size_t& actualRows, size_t& actualCols, size_t& actualTotalSize ) {
            actualRows = rows;
            actualCols = cols;
            actualTotalSize = totalSize;
        }

        template<typename Index_T = size_t >
        HOST_DEVICE static Index_T index(const size_t i, const size_t j,
                                         [[maybe_unused]] const size_t rows, [[maybe_unused]] const size_t cols,
                                         [[maybe_unused]] const size_t /*actualRows*/, [[maybe_unused]] const size_t /*actualCols*/) {
            if constexpr (mem_type == row_major) {
                return i * cols + j;
            } else {
                return j * rows + i;
            }
        }
    };

}

#endif //WARPLIB_GENERICLAYOUT_HPP