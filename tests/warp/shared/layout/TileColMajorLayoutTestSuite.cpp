//
// Created by Steven Roddan on 1/19/2026.
//

#include <warp/shared/layout/TileColMajorLayout.hpp>
#include <gtest/gtest.h>
using namespace warp::mem::layout;

TEST(TileColMajorLayoutTestSuite, VerifyTileEdgesWork_3x3_3x4_4x3_4x4)
{
    constexpr size_t rows = 9;
    constexpr size_t cols = 8;
    constexpr size_t actualRows = 12;
    constexpr size_t actualCols = 8;
    constexpr size_t tileSize = 4;

    ASSERT_EQ(15, TileColMajorLayout<tileSize>::index(3,3,rows, cols, actualRows, actualCols));
    ASSERT_EQ(51, TileColMajorLayout<tileSize>::index(3,4,rows, cols, actualRows, actualCols));
    ASSERT_EQ(28, TileColMajorLayout<tileSize>::index(4,3,rows, cols, actualRows, actualCols));
    ASSERT_EQ(64, TileColMajorLayout<tileSize>::index(4,4,rows, cols, actualRows, actualCols));
}