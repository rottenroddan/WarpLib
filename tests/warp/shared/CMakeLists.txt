add_executable(WarpLib_Shared_Tests
    layout/TileRowMajorLayoutTestSuite.cpp
    layout/TileColMajorLayoutTestSuite.cpp
)

target_link_libraries(WarpLib_Shared_Tests
        PRIVATE
        WarpLibHost
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(WarpLib_Shared_Tests)