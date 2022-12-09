cmake_minimum_required(VERSION 3.22)

set(YEAR 2022)
set(DAY 9)

project("${YEAR} Day ${DAY}" LANGUAGES CXX)

add_compile_definitions(DAY=day_${DAY})
add_compile_definitions(YEAR=year_${YEAR})

include_directories(..)
include_directories(../..)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${YEAR}_day_${DAY} ../../main.cpp ../../aoc.cpp day_${DAY}.cpp input)
