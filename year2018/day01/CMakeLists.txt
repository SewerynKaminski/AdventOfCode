cmake_minimum_required(VERSION 3.27)

set(YEAR 2018)
set(DAY 01)

project("${YEAR} Day ${DAY}" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(..)
include_directories(../..)

add_compile_definitions(DAY=day_${DAY})
add_compile_definitions(YEAR=year_${YEAR})

add_executable(${YEAR}_day_${DAY}
    ../../main.cpp
    ../../aoc.cpp
    day_${DAY}.cpp
    input
)
