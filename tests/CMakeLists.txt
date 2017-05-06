set(TEST_EXECUTABLE_NAME ${PROJECT_NAME}.Tests)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/catch)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/fakeit)
include_directories(../3rdparty)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DPLUGINS_DIR=\"${CMAKE_SOURCE_DIR}/src/plugins\")
add_definitions(-DTEST_SUITE=1)

set(CMAKE_AUTOMOC OFF)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${TEST_EXECUTABLE_NAME}
                      ${PROJECT_NAME}.Entities
                      ${PROJECT_NAME}.UseCases
                      ${PROJECT_NAME}.Presentation
                      ${PROJECT_NAME}.Infrastructure)
qt5_use_modules(${TEST_EXECUTABLE_NAME} Core Test)

add_test (NAME ${TEST_EXECUTABLE_NAME} COMMAND $<TARGET_FILE:${TEST_EXECUTABLE_NAME}>)
if(${ENABLE_COVERAGE})
    setup_target_for_coverage(coverage ${TEST_EXECUTABLE_NAME} coverage)
endif()