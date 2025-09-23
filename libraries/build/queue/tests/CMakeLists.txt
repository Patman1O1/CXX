#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(queue-tests)


#----------------------------------------------------------------------------------------------------------------------
# Settings and Options
#----------------------------------------------------------------------------------------------------------------------
include("../cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    enable_testing()
endif()


#----------------------------------------------------------------------------------------------------------------------
# Testing Framework (GoogleTest)
#----------------------------------------------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/heads/main.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # do not override parent project's runtime settings on Windows
set(INSTALL_GTEST OFF)

# For simplicity, always build googletest as static library. This prevents queue-tests executable from
# complaining about missing googletest DLLs on Windows.
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(googletest)


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------
if(is_top_level)
    find_package(queue REQUIRED)
endif()


#----------------------------------------------------------------------------------------------------------------------
# Target
#----------------------------------------------------------------------------------------------------------------------
set(SOURCES queue_tests.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_executable(queue-tests)

target_sources(queue-tests PRIVATE ${SOURCES})

target_link_libraries(queue-tests
    PRIVATE
        queue::queue
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
        pthread)

include(GoogleTest)
gtest_discover_tests(queue-tests)
