enable_testing()
add_subdirectory(warp/host)
add_subdirectory(warp/device)
add_subdirectory(warp/shared)


add_test(NAME DeviceTests COMMAND WarpLib_Device_Tests)
add_test(NAME SharedTests COMMAND WarpLib_Shared_Tests)