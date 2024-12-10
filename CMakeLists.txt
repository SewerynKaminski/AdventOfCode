cmake_minimum_required(VERSION 3.29)

project(AoC LANGUAGES CXX)

#include(ExternalProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

function (addday DAY)
    add_subdirectory(./year${YEAR}/day${DAY}/ )
endfunction()

add_custom_target(AoC SOURCES README.md)
#add_subdirectory(./year${YEAR}/day${DAY}/ ./year${YEAR}/day${DAY}/build )
#ExternalProject_Add(${YEAR}_day_${DAY}
#	SOURCE_DIR ./year${YEAR}/day${DAY}/
#	PREFIX ./year${YEAR}/day${DAY}/
#	SOURCE_SUBDIR ../../../year${YEAR}/day${DAY}/
#	INSTALL_COMMAND ""
#)

#===============================================================================
set(YEAR 2018)
addday(01)
addday(02)
addday(03)
addday(04)

#===============================================================================
set(YEAR 2021)
addday(01)
addday(02)
addday(03)
addday(04)
addday(05)
addday(06)
addday(07)
addday(08)
addday(09)
addday(10)
addday(11)
#addday(12)
#addday(13)
#addday(14)
#addday(15)
#addday(16)
#addday(17)
#addday(18)
#addday(19)
#addday(20)
#addday(21)
#addday(22)
#addday(23)
#addday(24)
#addday(25)

#===============================================================================
set(YEAR 2022)
addday(1)
addday(2)
addday(3)
addday(4)
addday(5)
addday(6)
addday(7)
addday(8)
addday(9)
addday(10)
addday(11)
addday(12)
addday(13)
addday(14)
addday(15)
#addday(16)
#addday(17)
addday(18)
#addday(19)
#addday(20)
#addday(21)
#addday(22)

#===============================================================================
set(YEAR 2023)

#===============================================================================
set(YEAR 2024)
addday(01)
addday(02)
addday(03)
addday(04)
addday(05)
addday(06)
addday(07)
addday(08)
addday(09)
addday(10)

#===============================================================================
