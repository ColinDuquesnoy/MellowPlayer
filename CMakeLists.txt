cmake_minimum_required(VERSION 3.2)

if(APPLE)
    set(CMAKE_PREFIX_PATH /usr/local/opt/qt)
endif()

set(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
if (NOT BUILD_NUMBER)
    set(BUILD_NUMBER $ENV{APPVEYOR_BUILD_NUMBER})
    if (NOT BUILD_NUMBER)
        # use zero for local builds.
        set(BUILD_NUMBER 0)
    endif()
endif()


project(MellowPlayer VERSION 3.3.1.${BUILD_NUMBER})
set(CMAKE_VERBOSE_MAKEFILE FALSE)
# cache version in CMakeCache.txt, so that script can easily query current version
set(MELLOWPLAYER_VERSION "${MellowPlayer_VERSION}" CACHE STRING "")

include(cmake/Macros.cmake)

# Options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)
set_option(BUILD_TESTS OFF BOOL "TRUE to build the tests, FALSE to ignore them.")
set_option(ENABLE_COVERAGE OFF BOOL "True to build code coverage targerts")
set_option(ENABLE_LCOV_REPORT OFF BOOL "True to enable lcov coverage report. Default is False.")
set_option(STATIC_LIBSTDCPP OFF BOOL "True to link statically with libstdc++ and libgcc")
set_option(UPDATE_TRANSLATIONS OFF BOOL "True to update translations")
set_option(DEFAULT_THEME "Adaptive" STRING "The default theme (available: Default, Midna, MidnaDark, Breeze, BreezeDark, Deezer, Spotify,...)")
set_option(USE_PRECOMPILED_HEADER ON BOOL "(GNU/Linux Only) ON to enable usage of pre-compiled headers. Default is ON")
set_option(CHECK_QML_SYNTAX OFF BOOL "Whether to check for QML/Javascript syntax errors. Default is OFF")
if (UNIX)
    set_option(USE_LD_GOLD ON BOOL "Use GNU gold linker")
endif()


if (UNIX AND NOT APPLE)
    set(USE_LIBNOTIFY TRUE)
endif()

include(cmake/FindDependencies.cmake)
include_directories(3rdparty)
# Sources
if(ENABLE_COVERAGE)
    include(cmake/CodeCoverage.cmake)
endif()
include(cmake/Config.cmake)
include(cmake/InstallDirs.cmake)
include(cmake/Cotire.cmake)

add_subdirectory(src)
add_subdirectory(plugins)
if(BUILD_TESTS)
    enable_testing(true)
    add_subdirectory(tests)
endif()

# Summary
message(STATUS "Building MellowPlayer v${MellowPlayer_VERSION}")
message(STATUS "Build date: ${BUILD_DATE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Use pre-compiled headers: ${USE_PRECOMPILED_HEADER}")
message(STATUS "Default theme: ${DEFAULT_THEME}")
message(STATUS "Build tests: ${BUILD_TESTS}")
if (BUILD_TESTS)
    if (ENABLE_COVERAGE AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message("    [x] Code Coverage")
    else()
        message("    [ ] Code Coverage")
    endif()
    if (ENABLE_COVERAGE AND ENABLE_LCOV_REPORT AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message("    [x] LCOV Code Coverage Report")
    else()
        message("    [ ] LCOV Code Coverage Report")
    endif()
endif()