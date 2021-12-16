cmake_minimum_required(VERSION 3.21)

project(2021_day_16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day16 year2021/day16/main.cpp
                     year2021/day16/day_16.cpp
                     year2021/day16/day_16.h
                     )
