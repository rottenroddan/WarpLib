//
// Created by Steven Roddan on 1/19/2026.
//

#include <gtest/gtest.h>
#include <warp/host/resources/HostCacheAlignedResource.hpp>

#include "../../../../cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h"

TEST(HostCacheAlignedResourceTestSuite, HandlesAllocation) {
    constexpr int size = 512;
    const auto _ptr = warp::resource::HostCacheAlignedResource::allocate<int32_t>(size);
    ASSERT_NE(_ptr, nullptr);
    ASSERT_TRUE(reinterpret_cast<uint64_t>(_ptr) % std::hardware_destructive_interference_size == 0);
    std::cout << reinterpret_cast<uint64_t>(_ptr) << std::endl;
    for (int32_t i = 0; i < size; ++i) {
        _ptr[i] = i;
        ASSERT_EQ(_ptr[i], i);
    }
    warp::resource::HostCacheAlignedResource::deallocate(_ptr);
}

TEST(HostCacheAlignedResourceTestSuite, HandlesZeroingData) {
    constexpr int size = 512;
    const auto _ptr = warp::resource::HostCacheAlignedResource::allocate<int32_t>(size);
    ASSERT_NE(_ptr, nullptr);
    for (int32_t i{}; i < size; i++) {
        _ptr[i] = i;
    }
    warp::resource::HostCacheAlignedResource::zero(_ptr, size);
    for (uint32_t i{}; i < size; i++) {
        ASSERT_EQ(_ptr[i], 0);
    }
    warp::resource::HostCacheAlignedResource::deallocate(_ptr);
}