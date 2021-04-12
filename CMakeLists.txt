cmake_minimum_required(VERSION 3.10)
project(multiplication)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(multiplication
        grandentier.cpp
        grandentier.hpp
        multiplication.cpp
        tests.cpp)
