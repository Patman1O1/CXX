#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(circular_array
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
option(SINGLY_LIST_BUILD_TESTS "Build circular_array tests" ON)
option(SINGLY_LIST_BUILD_MAIN "Build circular_array main" ON)
option(SINGLY_LIST_BUILD_DOCS "Build circular_array documentation" OFF)
option(SINGLY_LIST_INSTALL "Generate target for installing circular_array" ${is_top_level})
set_if_undefined(SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/circular_array" CACHE STRING
    "Install path for circular_array package-related CMake files")

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

add_library(circular_array INTERFACE) # initialized below
add_library(circular_array::circular_array ALIAS circular_array)

if(NOT INTERFACE STREQUAL "INTERFACE")
    set(SOURCES
            include/circular_array/export.hpp
            include/circular_array/circular_array.hpp
            src/circular_array.cpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(circular_array PRIVATE ${SOURCES})

   target_compile_definitions(circular_array
        PUBLIC
            "$<$<STREQUAL:INTERFACE, STATIC>:SINGLY_LIST_STATIC_DEFINE>")

    target_include_directories(circular_array
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
else()
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
endif()

set_target_properties(circular_array PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(SINGLY_LIST_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME circular_array_tests COMMAND circular_array_tests)
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

    generate_export_header(circular_array EXPORT_FILE_NAME include/circular_array/${export_file_name})
endif()

if(SINGLY_LIST_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/circular_array-config.cmake.in circular_array-config.cmake
            INSTALL_DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(circular_array-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS circular_array EXPORT circular_array-export
        RUNTIME COMPONENT circular_array
        LIBRARY COMPONENT circular_array NAMELINK_COMPONENT circular_array-dev
        ARCHIVE COMPONENT circular_array-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT circular_array-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/circular_array/${export_file_name}"
        COMPONENT circular_array-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/circular_array")

    set(targets_file "circular_array-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "circular_array-static-targets.cmake")
    endif()

    install(EXPORT circular_array-export
        COMPONENT circular_array-dev
        FILE "${targets_file}"
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}"
        NAMESPACE circular_array::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/circular_array-config-version.cmake"
        COMPONENT circular_array-dev
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:circular_array>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:circular_array>/$<TARGET_FILE_PREFIX:circular_array>$<TARGET_FILE_BASE_NAME:circular_array>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT circular_array-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------


