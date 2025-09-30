#-----------------------------------------------------------------------------------------------------------------------
# Information
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(map
        VERSION 1.0.0
        DESCRIPTION ""
        LANGUAGES CXX)


#-----------------------------------------------------------------------------------------------------------------------
# Includes
#-----------------------------------------------------------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(cmake/utils.cmake)


#-----------------------------------------------------------------------------------------------------------------------
# Settings and Options
#-----------------------------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(BUILD_DOCS "Build map documentation" OFF)
set_if_undefined(MAP_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/map" CACHE STRING
    "Install path for map package-related CMake files")

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


#-----------------------------------------------------------------------------------------------------------------------
# Library Target
#-----------------------------------------------------------------------------------------------------------------------
add_library(map INTERFACE) # initialized below
add_library(adt::map ALIAS map)

set(SOURCES
    include/map/export.hpp
    include/map/map.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_sources(map
    PRIVATE
        include/map/map.hpp)

target_include_directories(map
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(map PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})


#-----------------------------------------------------------------------------------------------------------------------
# Tests Target
#-----------------------------------------------------------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)
add_test(NAME map_tests COMMAND map_tests)


#-----------------------------------------------------------------------------------------------------------------------
# Main Target
#-----------------------------------------------------------------------------------------------------------------------
add_subdirectory(main)


#-----------------------------------------------------------------------------------------------------------------------
# Documentation Target
#-----------------------------------------------------------------------------------------------------------------------
if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Install Target
#-----------------------------------------------------------------------------------------------------------------------
configure_package_config_file(
    cmake/map-config.cmake.in
    map-config.cmake
    INSTALL_DESTINATION "${MAP_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    map-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS map
    EXPORT map-export
)

install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT map-dev
)

install(
    EXPORT map-export
    COMPONENT map-dev
    FILE "${targets_file}"
    DESTINATION "${MAP_INSTALL_CMAKEDIR}"
    NAMESPACE adt::
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/map-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/map-config-version.cmake"
    COMPONENT map-dev
    DESTINATION "${MAP_INSTALL_CMAKEDIR}"
)


#-----------------------------------------------------------------------------------------------------------------------
# Uninstall Target
#-----------------------------------------------------------------------------------------------------------------------
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)


#-----------------------------------------------------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------------------------------------------------


