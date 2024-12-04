cmake_minimum_required(VERSION 3.29)

project(AoC LANGUAGES CXX)

#include(ExternalProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

function (addday YEAR DAY)
    #add_subdirectory(./year${YEAR}/day${DAY}/ ./year${YEAR}/day${DAY}/build )
    add_subdirectory(./year${YEAR}/day${DAY}/ )
endfunction()

add_custom_target(AoC SOURCES README.md)

set(YEAR 2021)
#add_subdirectory(./year${YEAR}/day${DAY}/ ./year${YEAR}/day${DAY}/build )
#ExternalProject_Add(${YEAR}_day_${DAY}
#	SOURCE_DIR ./year${YEAR}/day${DAY}/
#	PREFIX ./year${YEAR}/day${DAY}/
#	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
#	INSTALL_COMMAND ""
#)
addday(${YEAR} 1)
addday(${YEAR} 2)
addday(${YEAR} 3)
addday(${YEAR} 4)
addday(${YEAR} 5)
addday(${YEAR} 06)
addday(${YEAR} 07)
addday(${YEAR} 08)
#addday(${YEAR} 09)
addday(${YEAR} 10)
#addday(${YEAR} 11)
#addday(${YEAR} 12)
#addday(${YEAR} 13)
#addday(${YEAR} 14)
#addday(${YEAR} 15)
#addday(${YEAR} 16)
#addday(${YEAR} 17)
#addday(${YEAR} 18)
#addday(${YEAR} 19)
#addday(${YEAR} 20)
#addday(${YEAR} 21)
#addday(${YEAR} 22)
#addday(${YEAR} 23)
#addday(${YEAR} 24)
#addday(${YEAR} 25)

set(YEAR 2022)
addday(${YEAR} 1)
addday(${YEAR} 2)
addday(${YEAR} 3)
addday(${YEAR} 4)
addday(${YEAR} 5)
addday(${YEAR} 6)
addday(${YEAR} 7)
addday(${YEAR} 8)
addday(${YEAR} 9)
addday(${YEAR} 10)
addday(${YEAR} 11)
addday(${YEAR} 12)
addday(${YEAR} 13)
addday(${YEAR} 14)
addday(${YEAR} 15)
#addday(${YEAR} 16)
#addday(${YEAR} 17)
#addday(${YEAR} 18)
#addday(${YEAR} 19)
#addday(${YEAR} 20)
#addday(${YEAR} 21)
#addday(${YEAR} 22)

# set(YEAR 2023)

set(YEAR 2024)
addday(${YEAR} 1)
addday(${YEAR} 2)
addday(${YEAR} 3)
addday(${YEAR} 4)

