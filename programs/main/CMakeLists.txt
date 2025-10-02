#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(main
        VERSION 1.0.0
        DESCRIPTION ""
        LANGUAGES CXX)


#----------------------------------------------------------------------------------------------------------------------
# Settings and Options
#----------------------------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)

include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(MAIN_BUILD_DOCS "Build main documentation" OFF)

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


#----------------------------------------------------------------------------------------------------------------------
# Targets
#----------------------------------------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_sources(main PRIVATE ${SOURCES})

target_include_directories(main
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(main PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(MAIN_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------



