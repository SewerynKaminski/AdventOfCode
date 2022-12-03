cmake_minimum_required(VERSION 3.22)

project("2022 Day 2" LANGUAGES CXX)

set(YEAR 2022)
set(DAY 2)

add_compile_definitions(DAY=day_${DAY})
add_compile_definitions(YEAR=year_${YEAR})

include_directories(..)
include_directories(../..)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(2022_day_${DAY} ../../main.cpp ../../aoc.cpp day_${DAY}.cpp input)
