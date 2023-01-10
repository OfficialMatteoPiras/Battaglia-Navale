cmake_minimum_required(VERSION 3.23)
project(Battaglia_Navale)



set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(battaglia_navale
        main.cpp
        sources/coords.cpp
        sources/matrix.cpp
        sources/ship.cpp
        sources/player.cpp
        sources/game.cpp
        sources/replay.cpp
        sources/replayPlayer.cpp headers/replayPlayer.h)

add_executable(replay
        main.cpp
        sources/coords.cpp
        sources/matrix.cpp
        sources/ship.cpp
        sources/player.cpp
        sources/game.cpp
        sources/replay.cpp
        sources/replayPlayer.cpp)
