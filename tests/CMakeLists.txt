include_directories(${CMAKE_SOURCE_DIR}/3rdparty/catch)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/fakeit)
include_directories(../3rdparty)
include_directories(.)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DPLUGINS_DIR=\"${CMAKE_SOURCE_DIR}/src/plugins\")
add_definitions(-DTEST_SUITE=1)

set(CMAKE_AUTOMOC OFF)

macro(add_mellowplayer_test TEST_TYPE)
    set(TEST_EXECUTABLE_NAME ${PROJECT_NAME}.${TEST_TYPE})
    file(GLOB_RECURSE SOURCE_FILES ${TEST_TYPE}/*.cpp)
    file(GLOB_RECURSE HEADER_FILES *.hpp)
    file(GLOB_RECURSE MOCK_SOURCES Mocks/*.cpp)
    add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILES} ${MOCK_SOURCES} main.cpp)
    target_link_libraries(${TEST_EXECUTABLE_NAME}
            ${PROJECT_NAME}.Entities
            ${PROJECT_NAME}.Application
            ${PROJECT_NAME}.Presentation
            ${PROJECT_NAME}.Infrastructure)
    qt5_use_modules(${TEST_EXECUTABLE_NAME} Core Test)
    add_test (NAME ${TEST_EXECUTABLE_NAME} COMMAND $<TARGET_FILE:${TEST_EXECUTABLE_NAME}>)
endmacro()

add_mellowplayer_test("UnitTests")
add_mellowplayer_test("IntegrationTests")
if (UNIX AND NOT APPLE)
    add_mellowplayer_test("MprisTests")
endif()

if(${ENABLE_COVERAGE} AND ${ENABLE_LCOV_REPORT})
    setup_target_for_coverage(coverage "ctest" coverage)
endif()
