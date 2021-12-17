cmake_minimum_required(VERSION 3.21)

project(2021_Day_9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day9 main.cpp
                    day_9.cpp
                    day_9.h
)

