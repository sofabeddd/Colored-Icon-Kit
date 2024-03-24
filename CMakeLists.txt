cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(ColoredIconKit VERSION 2.0.0)

add_library(${PROJECT_NAME} SHARED
        src/main.cpp
        src/ColoredIconKit/AprilFools.hpp
        src/ColoredIconKit/ColorManager.hpp
        src/ColoredIconKit/ModSettings.hpp
        src/ColoredIconKit/ColorManager.cpp
        src/ColoredIconKit/AprilFools.cpp
        src/ColoredIconKit/ModSettings.cpp
        src/UI/ChangelogPopup.cpp
        src/UI/ChangelogPopup.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME} EXTERNALS geode.node-ids:1.8.1)
