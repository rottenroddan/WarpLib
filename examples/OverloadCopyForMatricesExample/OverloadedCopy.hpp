//
// Created by Steven Roddan on 1/26/2026.
//

#ifndef WARPLIB_OVERLOADEDCOPY_HPP
#define WARPLIB_OVERLOADEDCOPY_HPP

#include <warp/shared/detail.hpp>
#include <warp/shared/layout/MemoryLayout.hpp>
#include <concepts>
#include <iostream>

/**
 * copied and pasted a definition from one of the libraries layouts. Used as a POC of allowing
 * overloading of copy method.
 */
template<warp::mem::MemoryLayout mem_type = warp::mem::row_major>
class CustomLayout {
public:
    static constexpr bool is_tiled_layout{false};
    static constexpr warp::mem::MemoryLayout memory_major{mem_type};

    static constexpr void resize(const size_t rows, const size_t cols, const size_t totalSize, size_t& actualRows, size_t& actualCols, size_t& actualTotalSize ) {
        actualRows = rows;
        actualCols = cols;
        actualTotalSize = totalSize;
    }

    template<typename Index_T = size_t >
    static Index_T index(const size_t i, const size_t j,
                                     [[maybe_unused]] const size_t rows, [[maybe_unused]] const size_t cols,
                                     [[maybe_unused]] const size_t /*actualRows*/, [[maybe_unused]] const size_t /*actualCols*/) {
        if constexpr (mem_type == warp::mem::row_major) {
            return i * cols + j;
        } else {
            return j * rows + i;
        }
    }
};

namespace warp::transformers {
    template<typename DstMatrix, typename SrcMatrix>
    requires
        std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type> &&
        std::is_same_v<typename DstMatrix::layout_type,
                       CustomLayout<warp::mem::row_major>> &&
        std::is_same_v<typename SrcMatrix::layout_type,
                       CustomLayout<warp::mem::col_major>> &&
        DstMatrix::resource_type::cpu_accessible &&
        SrcMatrix::resource_type::cpu_accessible
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::user_priority)
    {
        std::cout << "Custom copy method.\n";
    }
}

#endif //WARPLIB_OVERLOADEDCOPY_HPP