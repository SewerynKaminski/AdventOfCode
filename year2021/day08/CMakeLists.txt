cmake_minimum_required(VERSION 3.21)

project(2021_Day_8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day8 main.cpp
                    day_8.cpp
                    day_8.h
)

