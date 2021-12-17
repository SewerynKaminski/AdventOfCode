cmake_minimum_required(VERSION 3.16)

project(2021_Day_7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day7 main.cpp
                    day_7.cpp
                    day_7.h
)

