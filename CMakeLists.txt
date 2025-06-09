cmake_minimum_required(VERSION 3.31)
project(gh)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_GENERATOR "Ninja")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(game)
add_subdirectory(external)
