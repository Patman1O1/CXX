#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(array
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
option(SINGLY_LIST_BUILD_TESTS "Build array tests" ON)
option(SINGLY_LIST_BUILD_MAIN "Build array main" ON)
option(SINGLY_LIST_BUILD_DOCS "Build array documentation" OFF)
option(SINGLY_LIST_INSTALL "Generate target for installing array" ${is_top_level})
set_if_undefined(SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/array" CACHE STRING
    "Install path for array package-related CMake files")

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

add_library(array INTERFACE) # initialized below
add_library(array::array ALIAS array)

if(NOT INTERFACE STREQUAL "INTERFACE")
    set(SOURCES
            include/array/export.hpp
            include/array/array.hpp
            src/array.cpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(array PRIVATE ${SOURCES})

   target_compile_definitions(array
        PUBLIC
            "$<$<STREQUAL:INTERFACE, STATIC>:SINGLY_LIST_STATIC_DEFINE>")

    target_include_directories(array
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
else()
    set(SOURCES
            include/array/export.hpp
            include/array/array.hpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(array
        PRIVATE
            include/array/array.hpp)

    target_include_directories(array
        INTERFACE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
endif()

set_target_properties(array PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(SINGLY_LIST_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME array_tests COMMAND array_tests)
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

    generate_export_header(array EXPORT_FILE_NAME include/array/${export_file_name})
endif()

if(SINGLY_LIST_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/array-config.cmake.in array-config.cmake
            INSTALL_DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(array-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS array EXPORT array-export
        RUNTIME COMPONENT array
        LIBRARY COMPONENT array NAMELINK_COMPONENT array-dev
        ARCHIVE COMPONENT array-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT array-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/array/${export_file_name}"
        COMPONENT array-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/array")

    set(targets_file "array-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "array-static-targets.cmake")
    endif()

    install(EXPORT array-export
        COMPONENT array-dev
        FILE "${targets_file}"
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}"
        NAMESPACE array::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/array-config-version.cmake"
        COMPONENT array-dev
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:array>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:array>/$<TARGET_FILE_PREFIX:array>$<TARGET_FILE_BASE_NAME:array>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT array-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------


