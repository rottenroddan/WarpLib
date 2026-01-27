//
// Created by Steven Roddan on 1/25/2026.
//

#ifndef WARPLIB_COMMON_HPP
#define WARPLIB_COMMON_HPP

namespace warp::common {
    template<typename A, typename B>
    [[maybe_unused]]
    bool isSameDimensions(const A& Dst, const B& src ) {
        return Dst.getRows() == src.getRows() && Dst.getCols() == src.getCols();
    }

    template<typename A, typename B>
    [[maybe_unused]]
    bool isExactSameDimensions(const A& Dst, const B& src ) {
        return Dst.getRows() == src.getRows() && Dst.getCols() == src.getCols() &&
            Dst.getActualRows() == src.getActualRows() && Dst.getActualCols() == src.getActualCols();
    }
}

#endif //WARPLIB_COMMON_HPP