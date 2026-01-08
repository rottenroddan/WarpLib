set(WARP_DEVICE_LIB WarpLibDevice)

file(GLOB DEVICE_SOURCES "*.cu")

add_library(${WARP_DEVICE_LIB} SHARED ${DEVICE_SOURCES})

target_include_directories(${WARP_DEVICE_LIB}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

# Export macros for Windows DLL
target_compile_definitions(${WARP_DEVICE_LIB} PRIVATE WARP_DEVICE_EXPORTS)

add_custom_command(TARGET WarpLibDevice POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:WarpLibDevice>        # DLL output
        ${WARP_BIN_DIR}
)

set_target_properties(${WARP_DEVICE_LIB} PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        POSITION_INDEPENDENT_CODE ON
)

target_compile_features(${WARP_DEVICE_LIB} PUBLIC cxx_std_20)