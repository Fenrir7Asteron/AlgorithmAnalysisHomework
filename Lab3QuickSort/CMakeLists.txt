cmake_minimum_required(VERSION 3.22)
project(Lab3QuickSort)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab3QuickSort main.cpp sort.h)

# Google_Tests_run target
add_subdirectory(SortTests/lib/googletest)

add_executable(Google_Tests_run SortTests/sort_tests.cpp sort.h)

target_include_directories(Google_Tests_run
        PRIVATE
        .)

target_link_libraries(Google_Tests_run gtest gtest_main)
