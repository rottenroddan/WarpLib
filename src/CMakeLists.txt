# Host code
file(GLOB_RECURSE HOST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/host/*.cpp"
)

set(WARP_HOST WarpLibHost)
add_library(${WARP_HOST} STATIC ${HOST_SOURCES})

if(WARPLIB_STATIC_ZERO_MEMORY_AFTER_FREE)
    target_compile_definitions(${WARP_HOST} PUBLIC WARPLIB_ZERO_MEMORY)
endif()

target_include_directories(${WARP_HOST}
        PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_compile_features(${WARP_HOST} PUBLIC cxx_std_20)

# Device code
add_subdirectory(device)

find_package(CUDAToolkit REQUIRED)

# Link device library
target_link_libraries(${WARP_HOST}
        PUBLIC WarpLibDevice CUDA::cudart)