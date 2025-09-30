#-----------------------------------------------------------------------------------------------------------------------
# Information
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(binary_search_tree
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

option(BUILD_DOCS "Build binary_search_tree documentation" OFF)
set_if_undefined(BINARY_SEARCH_TREE_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/binary_search_tree" CACHE STRING
    "Install path for binary_search_tree package-related CMake files")

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


#-----------------------------------------------------------------------------------------------------------------------
# Library Target
#-----------------------------------------------------------------------------------------------------------------------
add_library(binary_search_tree INTERFACE) # initialized below
add_library(adt::binary_search_tree ALIAS binary_search_tree)

set(SOURCES
    include/binary_search_tree/export.hpp
    include/binary_search_tree/binary_search_tree.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_sources(binary_search_tree
    PRIVATE
        include/binary_search_tree/binary_search_tree.hpp)

target_include_directories(binary_search_tree
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(binary_search_tree PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})


#-----------------------------------------------------------------------------------------------------------------------
# Tests Target
#-----------------------------------------------------------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)
add_test(NAME binary_search_tree_tests COMMAND binary_search_tree_tests)


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
    cmake/binary_search_tree-config.cmake.in
    binary_search_tree-config.cmake
    INSTALL_DESTINATION "${BINARY_SEARCH_TREE_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    binary_search_tree-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS binary_search_tree
    EXPORT binary_search_tree-export
)

install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT binary_search_tree-dev
)

install(
    EXPORT binary_search_tree-export
    COMPONENT binary_search_tree-dev
    FILE "${targets_file}"
    DESTINATION "${BINARY_SEARCH_TREE_INSTALL_CMAKEDIR}"
    NAMESPACE adt::
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/binary_search_tree-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/binary_search_tree-config-version.cmake"
    COMPONENT binary_search_tree-dev
    DESTINATION "${BINARY_SEARCH_TREE_INSTALL_CMAKEDIR}"
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
include_directories("${CMAKE_SOURCE_DIR}/libraries/interface/binary_tree/include/binary_tree/binary_tree.hpp")

