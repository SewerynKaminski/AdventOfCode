cmake_minimum_required(VERSION 3.21)

project(2021_day_16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(day7 year2021/day07/main.cpp
                     year2021/day07/day_7.cpp
                     year2021/day07/day_7.h
                     )

add_executable(day8 year2021/day08/main.cpp
                     year2021/day08/day_8.cpp
                     year2021/day08/day_8.h
                     )

add_executable(day9 year2021/day09/main.cpp
                     year2021/day09/day_9.cpp
                     year2021/day09/day_9.h
                     )

add_executable(day10 year2021/day10/main.cpp
                     year2021/day10/day_10.cpp
                     year2021/day10/day_10.h
                     )


add_executable(day11 year2021/day11/main.cpp
                     year2021/day11/day_11.cpp
                     year2021/day11/day_11.h
                     )

add_executable(day12 year2021/day12/main.cpp
                     year2021/day12/day_12.cpp
                     year2021/day12/day_12.h
                     )

add_executable(day13 year2021/day13/main.cpp
                     year2021/day13/day_13.cpp
                     year2021/day13/day_13.h
                     )


add_executable(day14 year2021/day14/main.cpp
                     year2021/day14/day_14.cpp
                     year2021/day14/day_14.h
                     )
                     
add_executable(day15 year2021/day15/main.cpp
                     year2021/day15/day_15.cpp
                     year2021/day15/day_15.h
                     )
                     
add_executable(day16 year2021/day16/main.cpp
                     year2021/day16/day_16.cpp
                     year2021/day16/day_16.h
                     )
                     
add_executable(day17 year2021/day17/main.cpp
                     year2021/day17/day_17.cpp
                     year2021/day17/day_17.h
                     )
                     
add_executable(day18 year2021/day18/main.cpp
                     year2021/day18/day_18.cpp
                     year2021/day18/day_18.h
                     )
                     
add_executable(day20 year2021/day20/main.cpp
                     year2021/day20/day_20.cpp
                     year2021/day20/day_20.h
                     )
                     
add_executable(day21 year2021/day21/main.cpp
                     year2021/day21/day_21.cpp
                     year2021/day21/day_21.h
                     )
                     
add_executable(day22 year2021/day22/main.cpp
                     year2021/day22/day_22.cpp
                     year2021/day22/day_22.h
                     )

include(ExternalProject)

set(YEAR 2022)
set(DAY 1)
ExternalProject_Add(${YEAR}_day_${DAY}
	SOURCE_DIR ./year${YEAR}/day${DAY}/
	PREFIX ./year${YEAR}/day${DAY}/
	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
	INSTALL_COMMAND ""
)

set(DAY 2)
ExternalProject_Add(${YEAR}_day_${DAY} 
	SOURCE_DIR ./year${YEAR}/day${DAY}/
	PREFIX ./year${YEAR}/day${DAY}/
	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
	INSTALL_COMMAND ""
)

set(DAY 3)
ExternalProject_Add(${YEAR}_day_${DAY} 
	SOURCE_DIR ./year${YEAR}/day${DAY}/
	PREFIX ./year${YEAR}/day${DAY}/
	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
	INSTALL_COMMAND ""
)

set(DAY 4)
ExternalProject_Add(${YEAR}_day_${DAY} 
	SOURCE_DIR ./year${YEAR}/day${DAY}/
	PREFIX ./year${YEAR}/day${DAY}/
	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
	INSTALL_COMMAND ""
)

set(DAY 5)
ExternalProject_Add(${YEAR}_day_${DAY} 
	SOURCE_DIR ./year${YEAR}/day${DAY}/
	PREFIX ./year${YEAR}/day${DAY}/
	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
	INSTALL_COMMAND ""
)

#include(${CMAKE_CURRENT_SOURCE_DIR}/year2022/day1/CMakeLists.txt)
#set(YEAR 2022)
#set(DAY 1)
#add_compile_definitions(DAY=day_${DAY})
#add_compile_definitions(YEAR=year_${YEAR})
#add_executable(${YEAR}day${DAY} main.cpp aoc.cpp year${YEAR}/day${DAY}/day_${DAY}.cpp)


