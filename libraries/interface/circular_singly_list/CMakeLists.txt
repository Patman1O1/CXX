#-----------------------------------------------------------------------------------------------------------------------
# Information
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(circular_singly_list
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

option(BUILD_DOCS "Build circular_singly_list documentation" OFF)
set_if_undefined(CIRCULAR_SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/circular_singly_list" CACHE STRING
    "Install path for circular_singly_list package-related CMake files")

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


#-----------------------------------------------------------------------------------------------------------------------
# Library Target
#-----------------------------------------------------------------------------------------------------------------------
add_library(circular_singly_list INTERFACE) # initialized below
add_library(adt::circular_singly_list ALIAS circular_singly_list)

set(SOURCES
    include/circular_singly_list/export.hpp
    include/circular_singly_list/circular_singly_list.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_sources(circular_singly_list
    PRIVATE
        include/circular_singly_list/circular_singly_list.hpp)

target_include_directories(circular_singly_list
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(circular_singly_list PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})


#-----------------------------------------------------------------------------------------------------------------------
# Tests Target
#-----------------------------------------------------------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)
add_test(NAME circular_singly_list_tests COMMAND circular_singly_list_tests)


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
    cmake/circular_singly_list-config.cmake.in
    circular_singly_list-config.cmake
    INSTALL_DESTINATION "${CIRCULAR_SINGLY_LIST_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    circular_singly_list-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS circular_singly_list
    EXPORT circular_singly_list-export
)

install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT circular_singly_list-dev
)

install(
    EXPORT circular_singly_list-export
    COMPONENT circular_singly_list-dev
    FILE "${targets_file}"
    DESTINATION "${CIRCULAR_SINGLY_LIST_INSTALL_CMAKEDIR}"
    NAMESPACE adt::
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/circular_singly_list-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/circular_singly_list-config-version.cmake"
    COMPONENT circular_singly_list-dev
    DESTINATION "${CIRCULAR_SINGLY_LIST_INSTALL_CMAKEDIR}"
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


