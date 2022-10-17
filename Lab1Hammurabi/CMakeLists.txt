cmake_minimum_required(VERSION 3.22)
project(Lab1Hammurabi)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Lab1Hammurabi
        Code/Game.cpp
        Code/Game.h
        Code/Lab1Hammurabi.cpp Code/IO/MessagePrinter.cpp Code/IO/MessagePrinter.h Code/Data/GameData.cpp Code/Data/GameData.h Code/Data/GameConfig.cpp Code/Data/GameConfig.h Code/IO/UserInputManager.cpp Code/IO/UserInputManager.h Code/DataStructures/NumberRange.cpp Code/DataStructures/NumberRange.h Code/DataStructures/RoundInput.cpp Code/DataStructures/RoundInput.h Code/Utils/Random.cpp Code/Utils/Random.h Code/Data/PersistentGameData.h)

configure_file(${CMAKE_SOURCE_DIR}/res/gameConfig.txt ${CMAKE_CURRENT_BINARY_DIR}/res/gameConfig.txt COPYONLY)