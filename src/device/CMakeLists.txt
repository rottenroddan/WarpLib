set(WARP_DEVICE_LIB WarpLibDevice)

file(GLOB DEVICE_SOURCES "*.cu")

# Build DLL
add_library(${WARP_DEVICE_LIB} SHARED ${DEVICE_SOURCES})

target_include_directories(${WARP_DEVICE_LIB}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${WARP_DEVICE_LIB} PRIVATE WARP_DEVICE_EXPORTS)

set_target_properties(${WARP_DEVICE_LIB} PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        POSITION_INDEPENDENT_CODE ON
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
#        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
)

target_compile_features(${WARP_DEVICE_LIB} PUBLIC cxx_std_20)

# Define a list of example targets (names only)
get_property(DLL_EXAMPLE_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)

foreach(exe ${DLL_EXAMPLE_TARGETS})
    add_custom_command(TARGET WarpLibDevice POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:WarpLibDevice>
            $<TARGET_FILE_DIR:${exe}>/$<TARGET_FILE_NAME:WarpLibDevice>
            COMMENT "Copying WarpLibDevice.dll to $<TARGET_FILE_DIR:${exe}>"
    )
endforeach()