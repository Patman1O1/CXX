#-----------------------------------------------------------------------------------------------------------------------
# Variable Configuration
#-----------------------------------------------------------------------------------------------------------------------
# Set library variables
set(LIBRARY_NAME "" CACHE STRING "LIBRARY_NAME") # Required

set(LIBRARY_NAME_UPPER "${LIBRARY_NAME}" CACHE STRING "LIBRARY_NAME_UPPER")
string(TOUPPER "${LIBRARY_NAME_UPPER}" LIBRARY_NAME_UPPER)

set(LIBRARY_NAME_LOWER "${LIBRARY_NAME}" CACHE STRING "LIBRARY_NAME_LOWER")
string(TOLOWER "${LIBRARY_NAME_LOWER}" LIBRARY_NAME_LOWER)

set(LIBRARY_NAMESPACE "" CACHE STRING "LIBRARY_NAMESPACE")

set(LIBRARY_TYPE "" CACHE STRING "LIBRARY_TYPE \"\^(INTERFACE|STATIC|SHARED)\$\"") # Required
string(TOUPPER "${LIBRARY_TYPE}" LIBRARY_TYPE)

set(LIBRARY_TYPE_LOWER "${LIBRARY_TYPE}" CACHE STRING "LIBRARY_TYPE_LOWER")
string(TOLOWER "${LIBRARY_TYPE}" LIBRARY_TYPE_LOWER)

set(LIBRARY_DESCRIPTION "\"\"" CACHE STRING "LIBRARY_DESCRIPTION")
set(LIBRARY_VERSION 1.0.0)
set(LIBRARY_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libraries/${LIBRARY_TYPE_LOWER}/${LIBRARY_NAME}")
set(LIBRARY_BINARY_DIR "${CMAKE_BINARY_DIR}/libraries/${LIBRARY_TYPE_LOWER}/${LIBRARY_NAME}/build/${LIBRARY_NAME}")
set(TEMPLATE_DIR "${CMAKE_SOURCE_DIR}/libraries/${LIBRARY_TYPE_LOWER}/__template__")

# Set CMake and C++ related variables
set(CMAKE_VERSION 3.15...4.0)
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.15...4.0)
set(CMAKE_CXX_STANDARD 23)


# Fail the configuration process if the user does not specify a library name
if (NOT LIBRARY_NAME)
    message(FATAL_ERROR "-DLIBRARY_NAME was not specified")
endif()

# Fail the configuration process if the user does not specify a valid library type
if (NOT LIBRARY_TYPE MATCHES "^(INTERFACE|STATIC|SHARED)$")
    message(FATAL_ERROR "-DLIBRARY_TYPE was not specified as INTERFACE, STATIC, or SHARED")
endif()

# Set the library's namespace to the name of the library if no name is specified
if (NOT LIBRARY_NAMESPACE)
    set(LIBRARY_NAMESPACE ${LIBRARY_NAME})
endif()

# Prompt user of creation
message("Creating ${LIBRARY_NAME}...")


#-----------------------------------------------------------------------------------------------------------------------
# Source Directory Configuration
#-----------------------------------------------------------------------------------------------------------------------
# Create the library's source directories
file(MAKE_DIRECTORY "${LIBRARY_SOURCE_DIR}")
file(MAKE_DIRECTORY "${LIBRARY_SOURCE_DIR}/cmake")
file(MAKE_DIRECTORY "${LIBRARY_SOURCE_DIR}/include/${LIBRARY_NAME}")
file(MAKE_DIRECTORY "${LIBRARY_SOURCE_DIR}/main")
file(MAKE_DIRECTORY "${LIBRARY_SOURCE_DIR}/tests")

# Configure ${LIBRARY_NAME}
configure_file(
        "${TEMPLATE_DIR}/CMakeLists.txt.in"
        "${LIBRARY_SOURCE_DIR}/CMakeLists.txt"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/CMakePresets.json.in"
        "${LIBRARY_SOURCE_DIR}/CMakePresets.json"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/.clang-format.in"
        "${LIBRARY_SOURCE_DIR}/.clang-format"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/.gitignore.in"
        "${LIBRARY_SOURCE_DIR}/.gitignore"
        @ONLY
)

# Configure ${LIBRARY_NAME}/include/${LIBRARY_NAME}
configure_file(
        "${TEMPLATE_DIR}/include/__template__/__template__.hpp.in"
        "${LIBRARY_SOURCE_DIR}/include/${LIBRARY_NAME}/${LIBRARY_NAME}.hpp"
        @ONLY
)

# Configure ${LIBRARY_NAME}/src (if ${LIBRARY_TYPE} is NOT INTERFACE)
if(NOT LIBRARY_TYPE MATCHES "INTERFACE")
    configure_file(
            "${TEMPLATE_DIR}/src/__template__.cpp.in"
            "${LIBRARY_SOURCE_DIR}/src/${LIBRARY_NAME}.cpp"
            @ONLY
    )
endif()

# Configure ${LIBRARY_NAME}/src
configure_file(
        "${TEMPLATE_DIR}/main/CMakeLists.txt.in"
        "${LIBRARY_SOURCE_DIR}/main/CMakeLists.txt"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/main/main.cpp.in"
        "${LIBRARY_SOURCE_DIR}/main/main.cpp"
        @ONLY
)

# Configure ${LIBRARY_NAME}/tests
configure_file(
        "${TEMPLATE_DIR}/tests/CMakeLists.txt.in"
        "${LIBRARY_SOURCE_DIR}/tests/CMakeLists.txt"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/tests/__template___tests.cpp.in"
        "${LIBRARY_SOURCE_DIR}/tests/${LIBRARY_NAME}_tests.cpp"
        @ONLY
)

# Configure ${LIBRARY_NAME}/cmake
configure_file(
        "${TEMPLATE_DIR}/cmake/__template__-config.cmake.in.in"
        "${LIBRARY_SOURCE_DIR}/cmake/${LIBRARY_NAME}-config.cmake.in"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/cmake/silent_copy.cmake.in"
        "${LIBRARY_SOURCE_DIR}/cmake/silent_copy.cmake"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/cmake/utils.cmake.in"
        "${LIBRARY_SOURCE_DIR}/cmake/utils.cmake"
        @ONLY
)

configure_file(
        "${TEMPLATE_DIR}/cmake/cmake_uninstall.cmake.in.in"
        "${LIBRARY_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        @ONLY
)


#-----------------------------------------------------------------------------------------------------------------------
# Symbolic Link Configuration
#-----------------------------------------------------------------------------------------------------------------------
file(CREATE_LINK "${LIBRARY_SOURCE_DIR}" "libraries/symbolic-links/${LIBRARY_NAME}" SYMBOLIC)
file(CREATE_LINK "${CMAKE_SOURCE_DIR}/libraries" "${LIBRARY_SOURCE_DIR}/libraries" SYMBOLIC)


# Prompt user that the library was created
message("${LIBRARY_NAME} successfully created")

