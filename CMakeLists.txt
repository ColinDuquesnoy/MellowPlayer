cmake_minimum_required(VERSION 3.2)

set(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
if (NOT BUILD_NUMBER)
    set(BUILD_NUMBER $ENV{APPVEYOR_BUILD_NUMBER})
    if (NOT BUILD_NUMBER)
        # use zero for local builds.
        set(BUILD_NUMBER 0)
    endif()
endif()

project(MellowPlayer VERSION 3.0.0.${BUILD_NUMBER})

add_definitions(-DMELLOWPLAYER_VERSION="${MellowPlayer_VERSION}")
add_definitions(-DMELLOWPLAYER_VERSION_MAJOR="${MellowPlayer_VERSION_MAJOR}")
add_definitions(-DMELLOWPLAYER_VERSION_MINOR="${MellowPlayer_VERSION_MINOR}")
add_definitions(-DMELLOWPLAYER_VERSION_PATCH="${MellowPlayer_VERSION_PATCH}")
add_definitions(-DMELLOWPLAYER_VERSION_TWEAK="${MellowPlayer_VERSION_TWEAK}")
add_definitions(-DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

include(scripts/cmake/Macros.cmake)
include(scripts/cmake/Config.cmake)
include(scripts/cmake/InstallDirs.cmake)

# Options
set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release).")
set_option(BUILD_TESTS True BOOL "TRUE to build the tests, FALSE to ignore them.")
set_option(ENABLE_COVERAGE FALSE BOOL "True to build code coverage targerts")
set_option(ENABLE_LCOV_REPORT FALSE BOOL "True to enable lcov coverage report. Default is False.")

if (UNIX AND NOT APPLE)
    set(USE_LIBNOTIFY TRUE)
endif()

include(scripts/cmake/FindDependencies.cmake)

include_directories(lib)

# Sources
if(ENABLE_COVERAGE)
    include(scripts/cmake/CodeCoverage.cmake)
endif()
add_subdirectory(lib/MellowPlayer)
add_subdirectory(src)
if(BUILD_TESTS)
    enable_testing(true)
    add_subdirectory(tests)
endif()

install(DIRECTORY plugins DESTINATION ${CMAKE_INSTALL_DATADIR}/mellowplayer)
install(DIRECTORY share/applications DESTINATION ${CMAKE_INSTALL_DATADIR})
install(DIRECTORY share/icons DESTINATION ${CMAKE_INSTALL_DATADIR})

# Summary
message(STATUS "Building MellowPlayer v${MellowPlayer_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Testing enabled: ${BUILD_TESTS}")
message(STATUS "Code coverage enabled: ${ENABLE_COVERAGE}")
if (ENABLE_COVERAGE)
    message(STATUS "Generate lcov code coverage report: ${ENABLE_LCOV_REPORT}")
endif()