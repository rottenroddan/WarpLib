add_executable(WarpLib_Tests
        test.cpp
)

target_link_libraries(WarpLib_Tests
        PRIVATE
        WarpLibHost
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(WarpLib_Tests)