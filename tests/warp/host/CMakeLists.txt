add_executable(WarpLib_Host_Tests
        resources/TestGenericHostResource.cpp
)

target_link_libraries(WarpLib_Host_Tests
        PRIVATE
        WarpLibHost
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(WarpLib_Host_Tests)