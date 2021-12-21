cmake_minimum_required(VERSION 3.21)

project(2021_Day_21 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(day21 main.cpp
                     day_21.cpp
                     day_21.h
)
