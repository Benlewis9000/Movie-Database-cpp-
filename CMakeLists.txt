cmake_minimum_required(VERSION 3.15)
project(prog2cw2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -W -Wall -Wextra -pedantic")

add_executable(prog2cw2 main.cpp Movie.cpp Movie.h Certificate.cpp Certificate.h MovieDatabase.cpp MovieDatabase.h)