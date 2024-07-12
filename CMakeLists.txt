cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
        arduino-core
        URL https://github.com/arduino/ArduinoCore-avr/archive/refs/heads/master.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(./test/lib)

enable_testing()

add_executable(
        setting_selector_test
        test/src/selection/SettingSelector.test.cpp
)

add_executable(
        composite_motor_test
        test/src/motor/CompositeMotor.test.cpp
)

target_link_libraries(
        setting_selector_test
        GTest::gtest_main
)

target_link_libraries(
        composite_motor_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(setting_selector_test)
gtest_discover_tests(composite_motor_test)