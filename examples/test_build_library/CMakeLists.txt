add_executable(TestExample main.cpp)

target_link_libraries(TestExample
    PRIVATE WarpLibHost WarpLibDevice)