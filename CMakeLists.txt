cmake_minimum_required(VERSION 3.31)
project(gh_external)

set(CMAKE_CXX_STANDARD 26)

add_executable(game game/game.cpp)
add_executable(external external/external.cpp external/process.cpp)
