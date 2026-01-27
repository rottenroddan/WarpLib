//
// Created by Steven Roddan on 1/26/2026.
//

#ifndef WARPLIB_DETAIL_HPP
#define WARPLIB_DETAIL_HPP

namespace warp::detail {
    namespace internal {
        struct priority_0 { };
        struct priority_1 : priority_0 { };
        struct priority_2 : priority_1 { };
    }
    using user_priority = internal::priority_2;
}

#endif //WARPLIB_DETAIL_HPP