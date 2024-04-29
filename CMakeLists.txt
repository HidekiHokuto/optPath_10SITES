cmake_minimum_required(VERSION 3.24)
project(optPath_10SITES)

set(CMAKE_CXX_STANDARD 11)

include_directories("/opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3/Eigen")

add_executable(optPath_10SITES main.cpp)
