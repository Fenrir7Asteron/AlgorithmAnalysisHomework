cmake_minimum_required(VERSION 3.22)
project(Lab1Hammurabi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab1Hammurabi
        Code/Game.cpp
        Code/Game.h
        Code/Lab1Hammurabi.cpp Code/IO/MessagePrinter.cpp Code/IO/MessagePrinter.h Code/GameData.cpp Code/GameData.h Code/GameConfig.cpp Code/GameConfig.h Code/IO/UserInputManager.cpp Code/IO/UserInputManager.h Code/DataStructures/IntRange.cpp Code/DataStructures/IntRange.h Code/DataStructures/RoundInput.cpp Code/DataStructures/RoundInput.h)

configure_file(${CMAKE_SOURCE_DIR}/res/gameConfig.txt ${CMAKE_CURRENT_BINARY_DIR}/res/gameConfig.txt COPYONLY)