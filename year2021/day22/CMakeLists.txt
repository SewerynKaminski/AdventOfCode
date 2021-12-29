cmake_minimum_required(VERSION 3.21)

project("2021 Day 22" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(day22 main.cpp
                     day_22.cpp
                     day_22.h
)
