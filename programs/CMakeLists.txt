cmake_minimum_required(VERSION 4.1.1)
project(Programs LANGUAGES CXX)

# Variables
set(PROGRAM_NAME "" CACHE STRING "PROGRAM_NAME") # Required
set(PROGRAM_NAME_UPPER "${PROGRAM_NAME}" CACHE STRING "PROGRAM_NAME_UPPER")
set(PROGRAM_NAME_LOWER "${PROGRAM_NAME}" CACHE STRING "PROGRAM_NAME_LOWER")
set(PROGRAM_DESCRIPTION "\"\"" CACHE STRING "PROGRAM_DESCRIPTION")
set(PROGRAM_VERSION 1.0.0)
set(CMAKE_VERSION 3.15...4.0)
set(CMAKE_CXX_STANDARD 23)

# Variable Formatting
string(TOUPPER "${PROGRAM_NAME_UPPER}" PROGRAM_NAME_UPPER)
string(TOLOWER "${PROGRAM_NAME_LOWER}" PROGRAM_NAME_LOWER)


# Make sure required arguments were specified
if (NOT PROGRAM_NAME)
    message(FATAL_ERROR "-DPROGRAM_NAME was not specified")
endif()


# Configure ${PROGRAM_NAME}/src
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/src/main.cpp.in"
        "${PROJECT_BINARY_DIR}/${PROGRAM_NAME}/src/main.cpp"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/src/CMakeLists.txt.in"
        "${PROJECT_BINARY_DIR}/${PROGRAM_NAME}/src/CMakeLists.txt"
        @ONLY
)


# Configure ${PROGRAM_NAME}
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/.clang-format.in"
        "${PROJECT_BINARY_DIR}/${PROGRAM_NAME}/.clang-format"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/.gitignore.in"
        "${PROJECT_BINARY_DIR}/${PROGRAM_NAME}/.gitignore"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/CMakeLists.txt.in"
        "${PROJECT_BINARY_DIR}/${PROGRAM_NAME}/CMakeLists.txt"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/CMakePresets.json.in"
        "${PROJECT_BINARY_DIR}/${PROGRAM_NAME}/CMakePresets.json"
        @ONLY)


# Commands (these comments are temporary until the program builder is complete
# cmake -B build -DPROGRAM_NAME=mypro
# rm -r build && cmake -B build -DPROGRAM_NAME=mypro
