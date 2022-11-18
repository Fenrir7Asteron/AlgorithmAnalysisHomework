cmake_minimum_required(VERSION 3.22)
project(Lab2DynamicArray)

set(CMAKE_CXX_STANDARD 17)

# Lab2DynamicArray target
add_executable(Lab2DynamicArray Array.h playground_main.cpp)

# --------------------------

# Google_Tests_run target
add_subdirectory(ArrayTests/lib/googletest)

add_executable(Google_Tests_run ArrayTests/array_tests.cpp Array.h)

target_include_directories(Google_Tests_run
        PRIVATE
        .)

target_link_libraries(Google_Tests_run gtest gtest_main)
