#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake")
#include(../../../WarpLibHelpers.cmake)

function(create_multiple_host_test_definitions variant zero_after_free)
    set(target WarpLib_Host_Tests_${variant})

    add_executable(${target}
            resources/TestGenericHostResource.cpp
            resources/TestHostCacheAlignedResource.cpp
            matrix/MatrixTransformerTestSuite.cpp
    )

    target_link_libraries(${target}
            PRIVATE
            WarpLibHost
            GTest::gtest
            GTest::gtest_main
    )

    target_compile_definitions(${target}
            PRIVATE
            WARPLIB_ZERO_AFTER_FREE=${zero_after_free}
    )

    include(GoogleTest)
    #gtest_discover_tests(${target})

    add_test(
            NAME HostTests_${variant}
            COMMAND ${target}
    )

    set_tests_properties(HostTests_${variant}
            PROPERTIES LABELS "host;${zero_after_free}"
    )

    append_to_device_target(${target})
    copy_warplib_device(${target})
endfunction()


create_multiple_host_test_definitions(Zero_After_Free on)
create_multiple_host_test_definitions(Dont_Zero_After_Free off)