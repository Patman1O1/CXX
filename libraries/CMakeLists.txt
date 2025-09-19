cmake_minimum_required(VERSION 3.15...4.0)
project(Libraries LANGUAGES CXX)

# Variables
set(LIBRARY_NAME "" CACHE STRING "LIBRARY_NAME") # Required
set(LIBRARY_NAME_UPPER "${LIBRARY_NAME}" CACHE STRING "LIBRARY_NAME_UPPER")
set(LIBRARY_NAME_LOWER "${LIBRARY_NAME}" CACHE STRING "LIBRARY_NAME_LOWER")
set(LIBRARY_TYPE "" CACHE STRING "LIBRARY_TYPE \"\^(INTERFACE|STATIC|SHARED)\$\"") # Required
set(LIBRARY_DESCRIPTION "\"\"" CACHE STRING "LIBRARY_DESCRIPTION")
set(LIBRARY_VERSION 1.0.0)
set(CMAKE_VERSION 3.15...4.0)
set(CMAKE_CXX_STANDARD 23)

# Variable Formatting
string(TOUPPER "${LIBRARY_NAME_UPPER}" LIBRARY_NAME_UPPER)
string(TOLOWER "${LIBRARY_NAME_LOWER}" LIBRARY_NAME_LOWER)
string(TOUPPER "${LIBRARY_TYPE}" LIBRARY_TYPE)


# Make sure required arguments were specified
if (NOT LIBRARY_NAME)
    message(FATAL_ERROR "-DLIBRARY_NAME was not specified")
endif()

if (NOT LIBRARY_TYPE MATCHES "^(INTERFACE|STATIC|SHARED)$")
    message(FATAL_ERROR "-DLIBRARY_TYPE was not specified as INTERFACE, STATIC, or SHARED")
endif()


# Configure ${LIBRARY_NAME}/main
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/main/main.cpp.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/main/main.cpp"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/main/CMakeLists.txt.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/main/CMakeLists.txt"
        @ONLY
)

# Configure ${LIBRARY_NAME}/cmake
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/cmake/config-config.cmake.in.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/cmake/${LIBRARY_NAME}-config.cmake.in"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/cmake/silent_copy.cmake.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/cmake/silent_copy.cmake"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/cmake/utils.cmake.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/cmake/utils.cmake"
        @ONLY
)


# Configure ${LIBRARY_NAME}/include/${LIBRARY_NAME}
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/include/config/config.hpp.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/include/${LIBRARY_NAME}/${LIBRARY_NAME}.hpp"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/include/config/export.hpp.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/include/${LIBRARY_NAME}/export.hpp"
        @ONLY
)


# Configure ${LIBRARY_NAME}/src (if ${LIBRARY_TYPE} is NOT INTERFACE)
if(NOT LIBRARY_TYPE MATCHES "INTERFACE")
    configure_file(
            "${PROJECT_SOURCE_DIR}/config-files/build/src/config.cpp.in"
            "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/src/${LIBRARY_NAME}.cpp"
            @ONLY
    )
endif()


# Configure ${LIBRARY_NAME}/tests
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/tests/config_tests.cpp.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/tests/${LIBRARY_NAME}_tests.cpp"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/tests/CMakeLists.txt.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/tests/CMakeLists.txt"
        @ONLY
)

# Configure ${LIBRARY_NAME}
configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/.clang-format.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/.clang-format"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/.gitignore.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/.gitignore"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/CMakeLists.txt.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/CMakeLists.txt"
        @ONLY
)

configure_file(
        "${PROJECT_SOURCE_DIR}/config-files/build/CMakePresets.json.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/CMakePresets.json"
        @ONLY
)
