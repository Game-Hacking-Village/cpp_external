cmake_minimum_required(VERSION 3.31)
project(gh_external)

set(CMAKE_CXX_STANDARD 26)

# simple game
add_executable(game simple_game/simple_game.cpp)
# simple external (read and write memory)
add_executable(external_simple external/external_simple.cpp
        external/process.cpp external/memory.cpp)
# doom external (specifics to doom)
add_executable(external_doom external/external_doom.cpp
        external/process.cpp external/memory.cpp)
