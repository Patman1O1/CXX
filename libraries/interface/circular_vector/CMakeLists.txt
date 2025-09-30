#-----------------------------------------------------------------------------------------------------------------------
# Information
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(circular_vector
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

option(BUILD_DOCS "Build circular_vector documentation" OFF)
set_if_undefined(CIRCULAR_VECTOR_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/circular_vector" CACHE STRING
    "Install path for circular_vector package-related CMake files")

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


#-----------------------------------------------------------------------------------------------------------------------
# Library Target
#-----------------------------------------------------------------------------------------------------------------------
add_library(circular_vector INTERFACE) # initialized below
add_library(adt::circular_vector ALIAS circular_vector)

set(SOURCES
    include/circular_vector/export.hpp
    include/circular_vector/circular_vector.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_sources(circular_vector
    PRIVATE
        include/circular_vector/circular_vector.hpp)

target_include_directories(circular_vector
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(circular_vector PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})


#-----------------------------------------------------------------------------------------------------------------------
# Tests Target
#-----------------------------------------------------------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)
add_test(NAME circular_vector_tests COMMAND circular_vector_tests)


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
    cmake/circular_vector-config.cmake.in
    circular_vector-config.cmake
    INSTALL_DESTINATION "${CIRCULAR_VECTOR_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    circular_vector-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS circular_vector
    EXPORT circular_vector-export
)

install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT circular_vector-dev
)

install(
    EXPORT circular_vector-export
    COMPONENT circular_vector-dev
    FILE "${targets_file}"
    DESTINATION "${CIRCULAR_VECTOR_INSTALL_CMAKEDIR}"
    NAMESPACE adt::
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/circular_vector-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/circular_vector-config-version.cmake"
    COMPONENT circular_vector-dev
    DESTINATION "${CIRCULAR_VECTOR_INSTALL_CMAKEDIR}"
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


