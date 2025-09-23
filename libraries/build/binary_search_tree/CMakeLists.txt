#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(binary_search_tree
        VERSION 1.0.0
        DESCRIPTION ""
        LANGUAGES CXX)


#----------------------------------------------------------------------------------------------------------------------
# Settings and Options
#----------------------------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# SINGLY_LIST_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(SINGLY_LIST_BUILD_TESTS "Build binary_search_tree tests" ON)
option(SINGLY_LIST_BUILD_MAIN "Build binary_search_tree main" ON)
option(SINGLY_LIST_BUILD_DOCS "Build binary_search_tree documentation" OFF)
option(SINGLY_LIST_INSTALL "Generate target for installing binary_search_tree" ${is_top_level})
set_if_undefined(SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/binary_search_tree" CACHE STRING
    "Install path for binary_search_tree package-related CMake files")

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


#----------------------------------------------------------------------------------------------------------------------
# Targets
#----------------------------------------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)

add_library(binary_search_tree INTERFACE) # initialized below
add_library(binary_search_tree::binary_search_tree ALIAS binary_search_tree)

if(NOT INTERFACE STREQUAL "INTERFACE")
    set(SOURCES
            include/binary_search_tree/export.hpp
            include/binary_search_tree/binary_search_tree.hpp
            src/binary_search_tree.cpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(binary_search_tree PRIVATE ${SOURCES})

   target_compile_definitions(binary_search_tree
        PUBLIC
            "$<$<STREQUAL:INTERFACE, STATIC>:SINGLY_LIST_STATIC_DEFINE>")

    target_include_directories(binary_search_tree
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
else()
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
endif()

set_target_properties(binary_search_tree PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(SINGLY_LIST_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME binary_search_tree_tests COMMAND binary_search_tree_tests)
endif()

if(SINGLY_LIST_BUILD_MAIN)
    add_subdirectory(main)
endif()

if(SINGLY_LIST_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()

if(NOT INTERFACE STREQUAL "INTERFACE")
    include(GenerateExportHeader)
    set(export_file_name "export_shared.hpp")

    if(NOT INTERFACE STREQUAL "SHARED")
        set(export_file_name "export_static.hpp")
    endif()

    generate_export_header(binary_search_tree EXPORT_FILE_NAME include/binary_search_tree/${export_file_name})
endif()

if(SINGLY_LIST_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/binary_search_tree-config.cmake.in binary_search_tree-config.cmake
            INSTALL_DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(binary_search_tree-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS binary_search_tree EXPORT binary_search_tree-export
        RUNTIME COMPONENT binary_search_tree
        LIBRARY COMPONENT binary_search_tree NAMELINK_COMPONENT binary_search_tree-dev
        ARCHIVE COMPONENT binary_search_tree-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT binary_search_tree-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/binary_search_tree/${export_file_name}"
        COMPONENT binary_search_tree-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/binary_search_tree")

    set(targets_file "binary_search_tree-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "binary_search_tree-static-targets.cmake")
    endif()

    install(EXPORT binary_search_tree-export
        COMPONENT binary_search_tree-dev
        FILE "${targets_file}"
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}"
        NAMESPACE binary_search_tree::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/binary_search_tree-config-version.cmake"
        COMPONENT binary_search_tree-dev
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:binary_search_tree>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:binary_search_tree>/$<TARGET_FILE_PREFIX:binary_search_tree>$<TARGET_FILE_BASE_NAME:binary_search_tree>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT binary_search_tree-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------


