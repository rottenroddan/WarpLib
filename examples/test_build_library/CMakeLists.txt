add_executable(TestExample main.cpp)
target_link_libraries(TestExample PRIVATE WarpLibHost WarpLibDevice)
add_dependencies(TestExample WarpLibDevice)

#get_property(DLL_EXAMPLE_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)
#list(APPEND DLL_EXAMPLE_TARGETS TestExample)
#set_property(GLOBAL PROPERTY WarpLibDeviceTargets "${DLL_EXAMPLE_TARGETS}")

append_to_device_target(TestExample)
copy_warplib_device(TestExample)