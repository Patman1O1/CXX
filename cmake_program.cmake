# Variables
set(PROGRAM_NAME "" CACHE STRING "PROGRAM_NAME") # Required
set(PROGRAM_NAME_UPPER "${PROGRAM_NAME}" CACHE STRING "PROGRAM_NAME_UPPER")
string(TOUPPER "${PROGRAM_NAME_UPPER}" PROGRAM_NAME_UPPER)
set(PROGRAM_NAME_LOWER "${PROGRAM_NAME}" CACHE STRING "PROGRAM_NAME_LOWER")
string(TOLOWER "${PROGRAM_NAME_LOWER}" PROGRAM_NAME_LOWER)
set(PROGRAM_DESCRIPTION "\"\"" CACHE STRING "PROGRAM_DESCRIPTION")
set(PROGRAM_VERSION 1.0.0)
set(PROGRAM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/programs/${PROGRAM_NAME}")
set(PROGRAM_BINARY_DIR "${CMAKE_BINARY_DIR}/programs/${PROGRAM_NAME}/build/${PROGRAM_NAME}")
set(TEMPLATE_DIR "${CMAKE_SOURCE_DIR}/programs/__template__")

# Set CMake and C++ related variables
set(CMAKE_VERSION 3.15...4.0)
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.15...4.0)
set(CMAKE_CXX_STANDARD 23)

# Make sure required arguments were specified
if (NOT PROGRAM_NAME)
    message(FATAL_ERROR "-DPROGRAM_NAME was not specified")
endif()


# Configure ${PROGRAM_NAME}/src
configure_file(
        "${TEMPLATE_DIR}/src/main.cpp.in"
        "${PROGRAM_SOURCE_DIR}/src/main.cpp"
        @ONLY
)


# Configure ${PROGRAM_NAME}
configure_file(
        "${TEMPLATE_DIR}/.clang-format.in"
        "${PROGRAM_SOURCE_DIR}/.clang-format"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/.gitignore.in"
        "${PROGRAM_SOURCE_DIR}/.gitignore"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/CMakeLists.txt.in"
        "${PROGRAM_SOURCE_DIR}/CMakeLists.txt"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/CMakePresets.json.in"
        "${PROGRAM_SOURCE_DIR}/CMakePresets.json"
        @ONLY)


# Configure ${PROGRAM_NAME}/include
file(MAKE_DIRECTORY "${PROGRAM_SOURCE_DIR}/include")
