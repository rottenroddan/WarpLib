//
// Created by Steven Roddan on 12/29/2025.
//

#ifndef WARPLIB_LAYOUT_HPP
#define WARPLIB_LAYOUT_HPP

namespace warp::layout {
    enum MemoryLayout {DEFAULT, ROW_TILED, COL_TILED};

    class GenericLayout {
    public:
        static constexpr MemoryLayout getMajor() { return MemoryLayout::DEFAULT; }
        static constexpr void resize(size_t rows, size_t cols, size_t totalSize, size_t& actualRows, size_t& actualCols, size_t& actualTotalSize ) {
            actualRows = rows;
            actualCols = cols;
            actualTotalSize = totalSize;
        }
    };

}

#endif //WARPLIB_LAYOUT_HPP
