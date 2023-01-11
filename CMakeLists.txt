cmake_minimum_required(VERSION 3.23)

project(Battaglia_Navale)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -O2")

#includo le directory del progetto
include_directories(headers
        file
        sources)

#creo le librerie del progetto
add_library(Player
        headers/player.h
        sources/player.cpp)

add_library(coords
        headers/coords.h
        sources/coords.cpp)

add_library(game
        headers/game.h
        sources/game.cpp)

add_library(matrix
        headers/matrix.h
        sources/matrix.cpp)

add_library(Replay
        headers/replay.h
        sources/replay.cpp)

add_library(replayPlayer
        headers/replayPlayer.h
        sources/replayPlayer.cpp)

add_library(ship
        headers/ship.h
        sources/ship.cpp)

#creo gli eseguibili
add_executable(battaglia_navale
        main.cpp
        sources/coords.cpp
        sources/matrix.cpp
        sources/ship.cpp
        sources/player.cpp
        sources/game.cpp
        sources/replay.cpp
        sources/replayPlayer.cpp)

add_executable(replay
        main.cpp
        sources/coords.cpp
        sources/matrix.cpp
        sources/ship.cpp
        sources/player.cpp
        sources/game.cpp
        sources/replay.cpp
        sources/replayPlayer.cpp)
