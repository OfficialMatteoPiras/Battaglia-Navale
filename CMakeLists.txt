cmake_minimum_required(VERSION 3.23)
project(Battaglia_Navale)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Battaglia_Navale
        main.cpp
        sources/coords.cpp
        sources/player.cpp
        sources/ship.cpp
        sources/replay.cpp
        sources/game.cpp)
