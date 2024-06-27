cmake_minimum_required(VERSION 3.5)

project(
    str_utils
    LANGUAGES C
    DESCRIPTION "string utils library"
)

# ------------------------------------------------------------------------------

set(INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/str_utils/str_split.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/str_utils/str_starts_ends_with.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/str_utils/str_to_int.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/str_split.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/str_starts_ends_with.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/str_to_int.c
)

# ------------------------------------------------------------------------------

add_library(str_utils STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(str_utils
    PUBLIC
        ${INCLUDE_DIRECTORIES}
)

target_compile_options(str_utils
    PRIVATE
        -Wall -Wextra -Werror
        -pedantic -pedantic-errors
        #-ansi # <-- 'ANSI C' dont forced, since it the same as force C89 standard
)

set_target_properties(str_utils
    PROPERTIES
        # Even if libary itself written with C89/C90 standard support
        # (C_STANDARD 90), we dont force it - so library will be built by using
        # parent-project settings.
        #
        # That allow us to use 'long long' type (available since C99), if parent
        # project uses that standard.
        #
        #   C_STANDARD 90 # C89/C90
        #   C_STANDARD_REQUIRED on
        #   C_EXTENSIONS off

        # Tell the target these headers are "public"
        PUBLIC_HEADER "${HEADERS}"
)

# ------------------------------------------------------------------------------

include(GNUInstallDirs) # Needed to be able to create 'str_utils', 'static', 'shared' sub-directories
install(TARGETS str_utils
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/str_utils # public headers install destination: installed_dir/include/srt_utils/
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}/static        # static library install destination: installed_dir/lib/static/
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}/shared        # shared library install destination: installed_dir/lib/shared/
)
