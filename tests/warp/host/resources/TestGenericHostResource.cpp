//
// Created by steve on 1/14/2026.
//

#include <gtest/gtest.h>
#include <warp/host/resources/GenericHostResource.hpp>

TEST(GenericHostResourceTestSuite, HandlesAllocation) {
    constexpr int size = 512;
    const auto _ptr = warp::mem::resource::GenericHostResource::allocate<int32_t>(size);
    ASSERT_NE(_ptr, nullptr);
    for (int32_t i = 0; i < size; ++i) {
        _ptr[i] = i;
        ASSERT_EQ(_ptr[i], i);
    }
#ifndef WARPLIB_ZERO_MEMORY
    warp::resource::GenericHostResource::deallocate(_ptr);
#else
    warp::mem::resource::GenericHostResource::deallocate(_ptr, size);
#endif
}

TEST(GenericHostResourceTestSuite, HandlesZeroingData) {
    constexpr int size = 512;
    const auto _ptr = warp::mem::resource::GenericHostResource::allocate<int32_t>(size);
    ASSERT_NE(_ptr, nullptr);
    for (int32_t i{}; i < size; i++) {
        _ptr[i] = i;
    }
    warp::mem::resource::GenericHostResource::zero(_ptr, size);
    for (uint32_t i{}; i < size; i++) {
        ASSERT_EQ(_ptr[i], 0);
    }
#ifndef WARPLIB_ZERO_MEMORY
    warp::resource::GenericHostResource::deallocate(_ptr);
#else
    warp::mem::resource::GenericHostResource::deallocate(_ptr, size);
#endif
}