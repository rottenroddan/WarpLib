#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
#include(../WarpLibHelpers.cmake)

add_subdirectory(test_build_library)
add_subdirectory(another_directory)
add_subdirectory(PrintTiledIndices)
#add_subdirectory(OverloadCopyForMatricesExample)