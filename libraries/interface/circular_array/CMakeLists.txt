#-----------------------------------------------------------------------------------------------------------------------
# Information
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(circular_array
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

option(BUILD_DOCS "Build circular_array documentation" OFF)
set_if_undefined(CIRCULAR_ARRAY_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/circular_array" CACHE STRING
    "Install path for circular_array package-related CMake files")

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


#-----------------------------------------------------------------------------------------------------------------------
# Library Target
#-----------------------------------------------------------------------------------------------------------------------
add_library(circular_array INTERFACE) # initialized below
add_library(adt::circular_array ALIAS circular_array)

set(SOURCES
    include/circular_array/export.hpp
    include/circular_array/circular_array.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_sources(circular_array
    PRIVATE
        include/circular_array/circular_array.hpp)

target_include_directories(circular_array
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(circular_array PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})


#-----------------------------------------------------------------------------------------------------------------------
# Tests Target
#-----------------------------------------------------------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)
add_test(NAME circular_array_tests COMMAND circular_array_tests)


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
    cmake/circular_array-config.cmake.in
    circular_array-config.cmake
    INSTALL_DESTINATION "${CIRCULAR_ARRAY_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    circular_array-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS circular_array
    EXPORT circular_array-export
)

install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT circular_array-dev
)

install(
    EXPORT circular_array-export
    COMPONENT circular_array-dev
    FILE "${targets_file}"
    DESTINATION "${CIRCULAR_ARRAY_INSTALL_CMAKEDIR}"
    NAMESPACE adt::
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/circular_array-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/circular_array-config-version.cmake"
    COMPONENT circular_array-dev
    DESTINATION "${CIRCULAR_ARRAY_INSTALL_CMAKEDIR}"
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


