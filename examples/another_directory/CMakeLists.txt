add_executable(TestExample2 main.cpp)
target_link_libraries(TestExample2 PRIVATE WarpLibHost WarpLibDevice)
add_dependencies(TestExample2 WarpLibDevice)

#get_property(DLL_EXAMPLE_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)
#list(APPEND DLL_EXAMPLE_TARGETS TestExample)
#set_property(GLOBAL PROPERTY WarpLibDeviceTargets "${DLL_EXAMPLE_TARGETS}")

append_to_device_target(TestExample2)
