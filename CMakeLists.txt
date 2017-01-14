cmake_minimum_required(VERSION 3.2)

execute_process(COMMAND git rev-parse --short HEAD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE GIT_HASH
                OUTPUT_STRIP_TRAILING_WHITESPACE)

project(mellowplayer VERSION 3.0.0)

add_definitions(-DHACKEDIT_VERSION=${MellowPlayer_VERSION})
add_definitions(-DHACKEDIT_VERSION_MAJOR=${MellowPlayer_VERSION_MAJOR})
add_definitions(-DHACKEDIT_VERSION_MINOR=${MellowPlayer_VERSION_MINOR})
add_definitions(-DHACKEDIT_VERSION_PATCH=${MellowPlayer_VERSION_PATCH})

include(cmake/Macros.cmake)
include(cmake/Config.cmake)
include(cmake/Qt5Config.cmake)

# Options
set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release).")
set_option(BUILD_TESTS TRUE BOOL "TRUE to build the tests, FALSE to ignore them.")
set_option(ENABLE_COVERAGE FALSE BOOL "True to build code coverage targerts")

# Sources
add_subdirectory(src)
if(BUILD_TESTS)
    if(ENABLE_COVERAGE AND GCC_COMPILER)
        include(cmake/CodeCoverage.cmake)
    endif()
    add_subdirectory(tests)
endif()

# Summary
message(STATUS "Building MellowPlayer v${MellowPlayer_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build tests: ${BUILD_TESTS}")
