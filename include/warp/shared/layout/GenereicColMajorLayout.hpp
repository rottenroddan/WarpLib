//
// Created by Steven Roddan on 12/29/2025.
//

#ifndef WARPLIB_GENEREICROWMAJORLAYOUT_HPP
#define WARPLIB_GENEREICROWMAJORLAYOUT_HPP

#include <warp/shared/cuda_attr_expandables.hpp>
#include <warp/shared/layout/Indices.hpp>
#include <warp/shared/layout/MemoryLayout.hpp>

namespace warp::mem::layout {

    class GenericColMajorLayout {
    public:
        static constexpr MemoryLayout getMajor() { return MemoryLayout::COL_MAJOR; }
        static constexpr void resize(size_t rows, size_t cols, size_t totalSize, size_t& actualRows, size_t& actualCols, size_t& actualTotalSize ) {
            actualRows = rows;
            actualCols = cols;
            actualTotalSize = totalSize;
        }

        template<typename Index_T = size_t >
        HOST_DEVICE static inline Index_T index(size_t i, size_t j,
                                      size_t rows, size_t /*cols*/,
                                      size_t /*actualRows*/, size_t /*actualCols*/) {
            return j * rows + i;
        }
    };

}

#endif //WARPLIB_GENEREICROWMAJORLAYOUT_HPP
