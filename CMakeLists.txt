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

add_subdirectory( year2016 )

add_subdirectory( year2018 )
#add_subdirectory( year2019 )
#add_subdirectory( year2020 )
add_subdirectory( year2021 )
add_subdirectory( year2022 )
#add_subdirectory( year2023 )
add_subdirectory( year2024 )

#===============================================================================
