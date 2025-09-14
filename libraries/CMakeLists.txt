cmake_minimum_required(VERSION 4.0)
project(Libraries)

# Library name and type
set(LIBRARY_NAME "" CACHE STRING "LIBRARY_NAME")

# Fail the configuration process if the user does not specify a library name
if(NOT LIBRARY_NAME)
    message(FATAL_ERROR "-LIBRARY_NAME was not specified")
endif()

# Library directory
set(LIBRARY_DIR "${CMAKE_BINARY_DIR}/${LIBRARY_NAME}")

# L