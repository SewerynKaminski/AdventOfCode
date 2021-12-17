cmake_minimum_required(VERSION 3.21)

project(2021_Day_10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day10 main.cpp
                     day_10.cpp
                     day_10.h
)

