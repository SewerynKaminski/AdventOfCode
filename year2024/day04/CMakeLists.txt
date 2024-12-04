cmake_minimum_required(VERSION 3.29)

set(YEAR 2024)
set(DAY 04)

project("${YEAR} Day ${DAY}" LANGUAGES CXX)

add_compile_definitions(DAY=day_${DAY})
add_compile_definitions(YEAR=year_${YEAR})

include_directories(..)
include_directories(../..)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${YEAR}_day_${DAY} ../../main.cpp ../../aoc.cpp day_${DAY}.cpp input)
