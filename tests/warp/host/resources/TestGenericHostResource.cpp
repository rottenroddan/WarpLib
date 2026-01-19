//
// Created by steve on 1/14/2026.
//

#include <gtest/gtest.h>
#include <warp/host/resources/GenericHostResource.hpp>

TEST(GenericHostResourceTestSuite, HandlesAllocation) {
    constexpr int size = 512;
    const auto _ptr = warp::resource::GenericHostResource::allocate<int32_t>(size);
    ASSERT_NE(_ptr, nullptr);
    for (int32_t i = 0; i < size; ++i) {
        _ptr[i] = i;
        ASSERT_EQ(_ptr[i], i);
    }
    warp::resource::GenericHostResource::deallocate(_ptr);
}

TEST(GenericHostResourceTestSuite, HandlesZeroingData) {
    constexpr int size = 512;
    const auto _ptr = warp::resource::GenericHostResource::allocate<int32_t>(size);
    ASSERT_NE(_ptr, nullptr);
    for (int32_t i{}; i < size; i++) {
        _ptr[i] = i;
    }
    warp::resource::GenericHostResource::zero(_ptr, size);
    for (uint32_t i{}; i < size; i++) {
        ASSERT_EQ(_ptr[i], 0);
    }
    warp::resource::GenericHostResource::deallocate(_ptr);
}