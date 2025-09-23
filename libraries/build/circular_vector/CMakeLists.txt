#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(circular_vector
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
option(SINGLY_LIST_BUILD_TESTS "Build circular_vector tests" ON)
option(SINGLY_LIST_BUILD_MAIN "Build circular_vector main" ON)
option(SINGLY_LIST_BUILD_DOCS "Build circular_vector documentation" OFF)
option(SINGLY_LIST_INSTALL "Generate target for installing circular_vector" ${is_top_level})
set_if_undefined(SINGLY_LIST_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/circular_vector" CACHE STRING
    "Install path for circular_vector package-related CMake files")

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

add_library(circular_vector INTERFACE) # initialized below
add_library(circular_vector::circular_vector ALIAS circular_vector)

if(NOT INTERFACE STREQUAL "INTERFACE")
    set(SOURCES
            include/circular_vector/export.hpp
            include/circular_vector/circular_vector.hpp
            src/circular_vector.cpp)

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

    target_sources(circular_vector PRIVATE ${SOURCES})

   target_compile_definitions(circular_vector
        PUBLIC
            "$<$<STREQUAL:INTERFACE, STATIC>:SINGLY_LIST_STATIC_DEFINE>")

    target_include_directories(circular_vector
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
else()
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
endif()

set_target_properties(circular_vector PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(SINGLY_LIST_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME circular_vector_tests COMMAND circular_vector_tests)
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

    generate_export_header(circular_vector EXPORT_FILE_NAME include/circular_vector/${export_file_name})
endif()

if(SINGLY_LIST_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/circular_vector-config.cmake.in circular_vector-config.cmake
            INSTALL_DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(circular_vector-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS circular_vector EXPORT circular_vector-export
        RUNTIME COMPONENT circular_vector
        LIBRARY COMPONENT circular_vector NAMELINK_COMPONENT circular_vector-dev
        ARCHIVE COMPONENT circular_vector-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT circular_vector-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/circular_vector/${export_file_name}"
        COMPONENT circular_vector-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/circular_vector")

    set(targets_file "circular_vector-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "circular_vector-static-targets.cmake")
    endif()

    install(EXPORT circular_vector-export
        COMPONENT circular_vector-dev
        FILE "${targets_file}"
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}"
        NAMESPACE circular_vector::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/circular_vector-config-version.cmake"
        COMPONENT circular_vector-dev
        DESTINATION "${SINGLY_LIST_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:circular_vector>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:circular_vector>/$<TARGET_FILE_PREFIX:circular_vector>$<TARGET_FILE_BASE_NAME:circular_vector>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT circular_vector-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------


