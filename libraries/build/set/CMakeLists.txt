#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(set
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
option(SINGLY_LIST_BUILD_TESTS "Build set tests" ON)
option(SINGLY_LIST_BUILD_MAIN "Build set main" ON)
option(SINGLY_LIST_BUILD_DOCS "Build set documentation" OFF)
option(SINGLY_LIST_INSTALL "Generate target for installing set" ${is_top_level})
set_if_undefined(SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/set" CACHE STRING
    "Install path for set package-related CMake files")

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

add_library(set INTERFACE) # initialized below
add_library(set::set ALIAS set)

if(NOT INTERFACE STREQUAL "INTERFACE")
    set(SOURCES
            include/set/export.hpp
            include/set/set.hpp
            src/set.cpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(set PRIVATE ${SOURCES})

   target_compile_definitions(set
        PUBLIC
            "$<$<STREQUAL:INTERFACE, STATIC>:SINGLY_LIST_STATIC_DEFINE>")

    target_include_directories(set
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
else()
    set(SOURCES
            include/set/export.hpp
            include/set/set.hpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(set
        PRIVATE
            include/set/set.hpp)

    target_include_directories(set
        INTERFACE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
endif()

set_target_properties(set PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(SINGLY_LIST_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME set_tests COMMAND set_tests)
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

    generate_export_header(set EXPORT_FILE_NAME include/set/${export_file_name})
endif()

if(SINGLY_LIST_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/set-config.cmake.in set-config.cmake
            INSTALL_DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(set-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS set EXPORT set-export
        RUNTIME COMPONENT set
        LIBRARY COMPONENT set NAMELINK_COMPONENT set-dev
        ARCHIVE COMPONENT set-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT set-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/set/${export_file_name}"
        COMPONENT set-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/set")

    set(targets_file "set-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "set-static-targets.cmake")
    endif()

    install(EXPORT set-export
        COMPONENT set-dev
        FILE "${targets_file}"
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}"
        NAMESPACE set::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/set-config-version.cmake"
        COMPONENT set-dev
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:set>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:set>/$<TARGET_FILE_PREFIX:set>$<TARGET_FILE_BASE_NAME:set>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT set-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------


