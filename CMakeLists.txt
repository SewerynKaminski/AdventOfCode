cmake_minimum_required(VERSION 3.21)

project(AoC LANGUAGES CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

set(YEAR 2021)
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
add_executable(day7 year${YEAR}/day07/main.cpp
                    year${YEAR}/day07/day_7.cpp
                    year${YEAR}/day07/day_7.h
                    )

add_executable(day8 year${YEAR}/day08/main.cpp
                    year${YEAR}/day08/day_8.cpp
                    year${YEAR}/day08/day_8.h
                    )

add_executable(day9 year${YEAR}/day09/main.cpp
                    year${YEAR}/day09/day_9.cpp
                    year${YEAR}/day09/day_9.h
                    )

add_executable(day10 year${YEAR}/day10/main.cpp
                     year${YEAR}/day10/day_10.cpp
                     year${YEAR}/day10/day_10.h
                     )


add_executable(day11 year${YEAR}/day11/main.cpp
                     year${YEAR}/day11/day_11.cpp
                     year${YEAR}/day11/day_11.h
                     )

add_executable(day12 year${YEAR}/day12/main.cpp
                     year${YEAR}/day12/day_12.cpp
                     year${YEAR}/day12/day_12.h
                     )

add_executable(day13 year${YEAR}/day13/main.cpp
                     year${YEAR}/day13/day_13.cpp
                     year${YEAR}/day13/day_13.h
                     )


add_executable(day14 year${YEAR}/day14/main.cpp
                     year${YEAR}/day14/day_14.cpp
                     year${YEAR}/day14/day_14.h
                     )
                     
add_executable(day15 year${YEAR}/day15/main.cpp
                     year${YEAR}/day15/day_15.cpp
                     year${YEAR}/day15/day_15.h
                     )
                     
add_executable(day16 year${YEAR}/day16/main.cpp
                     year${YEAR}/day16/day_16.cpp
                     year${YEAR}/day16/day_16.h
                     )
                     
add_executable(day17 year${YEAR}/day17/main.cpp
                     year${YEAR}/day17/day_17.cpp
                     year${YEAR}/day17/day_17.h
                     )
                     
add_executable(day18 year${YEAR}/day18/main.cpp
                     year${YEAR}/day18/day_18.cpp
                     year${YEAR}/day18/day_18.h
                     )
                     
add_executable(day20 year${YEAR}/day20/main.cpp
                     year${YEAR}/day20/day_20.cpp
                     year${YEAR}/day20/day_20.h
                     )
                     
add_executable(day21 year${YEAR}/day21/main.cpp
                     year${YEAR}/day21/day_21.cpp
                     year${YEAR}/day21/day_21.h
                     )
                     
add_executable(day22 year${YEAR}/day22/main.cpp
                     year${YEAR}/day22/day_22.cpp
                     year${YEAR}/day22/day_22.h
                     )

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

set(DAY 6)
ExternalProject_Add(${YEAR}_day_${DAY} 
        SOURCE_DIR ./year${YEAR}/day${DAY}/
        PREFIX ./year${YEAR}/day${DAY}/
        SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
        INSTALL_COMMAND ""
)

set(DAY 7)
ExternalProject_Add(${YEAR}_day_${DAY} 
        SOURCE_DIR ./year${YEAR}/day${DAY}/
        PREFIX ./year${YEAR}/day${DAY}/
        SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
        INSTALL_COMMAND ""
)

set(DAY 8)
ExternalProject_Add(${YEAR}_day_${DAY}
        SOURCE_DIR ./year${YEAR}/day${DAY}/
        PREFIX ./year${YEAR}/day${DAY}/
        SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
        INSTALL_COMMAND ""
)

set(DAY 9)
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


