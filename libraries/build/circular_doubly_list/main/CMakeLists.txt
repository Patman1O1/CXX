#----------------------------------------------------------------------------------------------------------------------
# Information
#----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...4.0)
project(circular_doubly_list-main)


#----------------------------------------------------------------------------------------------------------------------
# Settings and Options
#----------------------------------------------------------------------------------------------------------------------
include("../cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)


#----------------------------------------------------------------------------------------------------------------------
# Dependencies
#----------------------------------------------------------------------------------------------------------------------
if(is_top_level)
    find_package(circular_doubly_list REQUIRED)
endif()


#----------------------------------------------------------------------------------------------------------------------
# Target
#----------------------------------------------------------------------------------------------------------------------
set(SOURCES main.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_executable(circular_doubly_list-main)

target_sources(circular_doubly_list-main PRIVATE ${SOURCES})

target_link_libraries(circular_doubly_list-main
    PRIVATE
        circular_doubly_list::circular_doubly_list
        pthread)
