//
// Created by Steven Roddan on 1/19/2026.
//

#ifndef WARPLIB_TILECOLMAJORLAYOUT_HPP
#define WARPLIB_TILECOLMAJORLAYOUT_HPP

#include <cmath>
#include <new>
#include <warp/shared/layout/MemoryLayout.hpp>
#include <warp/shared/cuda_attr_expandables.hpp>
namespace warp::mem::layout {
    template<size_t TileSize>
    class TileColMajorLayout {
    public:
        static constexpr size_t tile_size = TileSize;
        static constexpr bool is_tiled_layout{true};
        static constexpr MemoryLayout memory_major{row_major};

        static constexpr void resize(const size_t rows, const size_t cols, const size_t /*totalSize*/, size_t& actualRows, size_t& actualCols, size_t& actualTotalSize ) {
            actualRows = std::ceil(static_cast<double>(rows) / static_cast<double>(tile_size)) * tile_size;
            actualCols = std::ceil(static_cast<double>(cols) / static_cast<double>(tile_size)) * tile_size;
            actualTotalSize = actualRows * actualCols;
        }

        template<typename Index_T = size_t >
        HOST_DEVICE static Index_T index(const size_t i, const size_t j,
                                         const size_t /*rows*/ , const size_t /*cols*/ ,
                                         const size_t actualRows, const size_t /*actualCols*/) {
            return j / tile_size * (actualRows * tile_size) + i / tile_size * (tile_size * tile_size) + j % tile_size * tile_size + i % tile_size;
        }
    };
}
#endif //WARPLIB_TILECOLMAJORLAYOUT_HPP