function(append_to_device_target target)
    get_property(DLL_WARP_TARGETS GLOBAL PROPERTY WarpLibDeviceTargets)
    list(APPEND DLL_WARP_TARGETS ${target})
    set_property(GLOBAL PROPERTY WarpLibDeviceTargets "${DLL_WARP_TARGETS}")
endfunction()

function(copy_warplib_device exe)
    add_custom_command(TARGET ${exe} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:WarpLibDevice>
            $<TARGET_FILE_DIR:${exe}>
            COMMENT "Copying WarpLibDevice.dll next to ${exe}"
    )
endfunction()