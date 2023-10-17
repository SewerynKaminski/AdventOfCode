cmake_minimum_required(VERSION 3.21)

project("2021 Day 23" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(day23 main.cpp
    day_23.cpp
    day_23.h
)
