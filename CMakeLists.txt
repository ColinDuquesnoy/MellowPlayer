cmake_minimum_required(VERSION 3.5)

project(mellowplayer VERSION 3.0.0)

add_definitions(-DHACKEDIT_VERSION=${mellowplayer_VERSION})
add_definitions(-DHACKEDIT_VERSION_MAJOR=${mellowplayer_VERSION_MAJOR})
add_definitions(-DHACKEDIT_VERSION_MINOR=${mellowplayer_VERSION_MINOR})
add_definitions(-DHACKEDIT_VERSION_PATCH=${mellowplayer_VERSION_PATCH})

include(scripts/cmake/Macros.cmake)
include(scripts/cmake/Config.cmake)
include(scripts/cmake/Qt5Config.cmake)

# Options
set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release).")
set_option(BUILD_TESTS TRUE BOOL "TRUE to build the tests, FALSE to ignore them.")
set_option(ENABLE_COVERAGE FALSE BOOL "True to build code coverage targerts")

# Common headers
include_directories(lib/common/)

# Sources
if(ENABLE_COVERAGE)
    include(scripts/cmake/CodeCoverage.cmake)
endif()
add_subdirectory(lib)
add_subdirectory(src)
if(${BUILD_TESTS})
    enable_testing(true)
    add_subdirectory(tests)
endif()

# Summary
message(STATUS "Building MellowPlayer v${mellowplayer_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build tests: ${BUILD_TESTS}")
