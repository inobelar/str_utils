cmake_minimum_required(VERSION 3.5)

project(
    str_utils_tests
    LANGUAGES C
    DESCRIPTION "Tests for string utils library"
)

# ------------------------------------------------------------------------------

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

add_executable(str_utils_tests
    ${SOURCES}
)

# ------------------------------------------------------------------------------

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    str_utils_tests__str_utils
    EXCLUDE_FROM_ALL
)

target_link_libraries(str_utils_tests
    PRIVATE
        str_utils
)

# ------------------------------------------------------------------------------

target_compile_options(str_utils_tests
    PRIVATE
        -Wall -Wextra -Werror
        -pedantic -pedantic-errors
        -ansi
)

set_target_properties(str_utils_tests
    PROPERTIES
        C_STANDARD          90 # C90
        C_STANDARD_REQUIRED on
        C_EXTENSIONS        off
)
