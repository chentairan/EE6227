cmake_minimum_required(VERSION 3.20)
project(GA4)

set(CMAKE_CXX_STANDARD 14)

add_executable(GA3 main.cpp Genetic.cpp)

add_executable(GA4_island islandGA.cpp Genetic.cpp)
