cmake_minimum_required(VERSION 3.5)

project(MellowPlayer VERSION 3.0.0)

add_definitions(-DMELLOWPLAYER_VERSION="${MellowPlayer_VERSION}")
add_definitions(-DMELLOWPLAYER_VERSION_MAJOR="${MellowPlayer_VERSION_MAJOR}")
add_definitions(-DMELLOWPLAYER_VERSION_MINOR="${MellowPlayer_VERSION_MINOR}")
add_definitions(-DMELLOWPLAYER_VERSION_PATCH="${MellowPlayer_VERSION_PATCH}")
add_definitions(-DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

include(scripts/cmake/Macros.cmake)
include(scripts/cmake/Config.cmake)

# Options
set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release).")
set_option(BUILD_TESTS TRUE BOOL "TRUE to build the tests, FALSE to ignore them.")
set_option(ENABLE_COVERAGE FALSE BOOL "True to build code coverage targerts")

if (UNIX AND NOT APPLE)
    set(USE_LIBNOTIFY TRUE)
endif()

include(scripts/cmake/FindDependencies.cmake)

include_directories(lib/)

# Sources
if(ENABLE_COVERAGE)
    include(scripts/cmake/CodeCoverage.cmake)
endif()
add_subdirectory(lib)
add_subdirectory(src)
if(BUILD_TESTS)
    enable_testing(true)
    add_subdirectory(tests)
endif()

# Summary
message(STATUS "Building MellowPlayer v${MellowPlayer_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build tests: ${BUILD_TESTS}")
