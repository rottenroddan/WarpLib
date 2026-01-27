//
// Created by Steven Roddan on 1/26/2026.
//

#include "OverloadedCopy.hpp"
#include <warp/host/Matrix.hpp>

int main() {
    using namespace warp;
    Matrix<float, mem::resource::GenericHostResource, CustomLayout<warp::mem::row_major>> a(1,1);
    Matrix<float, mem::resource::GenericHostResource, CustomLayout<warp::mem::col_major>> b(1,1);

    static_assert(std::is_same_v<Matrix<float, mem::resource::GenericHostResource, CustomLayout<mem::MemoryLayout::row_major>>::layout_type,
            CustomLayout<mem::row_major>>);

    //example usage, should see custom message from copy function defined above.
    b.copyTo(a);
    return 0;
}