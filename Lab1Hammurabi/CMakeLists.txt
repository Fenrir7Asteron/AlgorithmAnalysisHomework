cmake_minimum_required(VERSION 3.22)
project(Lab1Hammurabi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab1Hammurabi
        Game.cpp
        Game.h
        Lab1Hammurabi.cpp MessagePrinter.cpp MessagePrinter.h GameData.cpp GameData.h GameConfig.cpp GameConfig.h UserInputManager.cpp UserInputManager.h)

configure_file(${CMAKE_SOURCE_DIR}/data/gameConfig.txt ${CMAKE_CURRENT_BINARY_DIR}/data/gameConfig.txt COPYONLY)