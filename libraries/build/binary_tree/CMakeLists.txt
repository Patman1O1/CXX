#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(binary_tree
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
option(SINGLY_LIST_BUILD_TESTS "Build binary_tree tests" ON)
option(SINGLY_LIST_BUILD_MAIN "Build binary_tree main" ON)
option(SINGLY_LIST_BUILD_DOCS "Build binary_tree documentation" OFF)
option(SINGLY_LIST_INSTALL "Generate target for installing binary_tree" ${is_top_level})
set_if_undefined(SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/binary_tree" CACHE STRING
    "Install path for binary_tree package-related CMake files")

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

add_library(binary_tree INTERFACE) # initialized below
add_library(binary_tree::binary_tree ALIAS binary_tree)

if(NOT INTERFACE STREQUAL "INTERFACE")
    set(SOURCES
            include/binary_tree/export.hpp
            include/binary_tree/binary_tree.hpp
            src/binary_tree.cpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(binary_tree PRIVATE ${SOURCES})

   target_compile_definitions(binary_tree
        PUBLIC
            "$<$<STREQUAL:INTERFACE, STATIC>:SINGLY_LIST_STATIC_DEFINE>")

    target_include_directories(binary_tree
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
else()
    set(SOURCES
            include/binary_tree/export.hpp
            include/binary_tree/binary_tree.hpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(binary_tree
        PRIVATE
            include/binary_tree/binary_tree.hpp)

    target_include_directories(binary_tree
        INTERFACE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
endif()

set_target_properties(binary_tree PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(SINGLY_LIST_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME binary_tree_tests COMMAND binary_tree_tests)
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

    generate_export_header(binary_tree EXPORT_FILE_NAME include/binary_tree/${export_file_name})
endif()

if(SINGLY_LIST_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/binary_tree-config.cmake.in binary_tree-config.cmake
            INSTALL_DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(binary_tree-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS binary_tree EXPORT binary_tree-export
        RUNTIME COMPONENT binary_tree
        LIBRARY COMPONENT binary_tree NAMELINK_COMPONENT binary_tree-dev
        ARCHIVE COMPONENT binary_tree-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT binary_tree-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/binary_tree/${export_file_name}"
        COMPONENT binary_tree-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/binary_tree")

    set(targets_file "binary_tree-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "binary_tree-static-targets.cmake")
    endif()

    install(EXPORT binary_tree-export
        COMPONENT binary_tree-dev
        FILE "${targets_file}"
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}"
        NAMESPACE binary_tree::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/binary_tree-config-version.cmake"
        COMPONENT binary_tree-dev
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:binary_tree>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:binary_tree>/$<TARGET_FILE_PREFIX:binary_tree>$<TARGET_FILE_BASE_NAME:binary_tree>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT binary_tree-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------


