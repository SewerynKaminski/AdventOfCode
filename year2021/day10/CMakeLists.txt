cmake_minimum_required(VERSION 3.21)

set(YEAR 2021)
set(DAY 10)

project(${YEAR}_day_${DAY} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -fmodules-ts)

include_directories(..)
include_directories(../..)

add_compile_definitions(DAY=day_${DAY})
add_compile_definitions(YEAR=year_${YEAR})

add_executable ( ${YEAR}_day_${DAY} ../../main.cpp ../../aoc.cpp day_${DAY}.cpp input )

