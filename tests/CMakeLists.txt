include_directories(${CMAKE_SOURCE_DIR}/3rdparty/catch)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/fakeit)
include_directories(../3rdparty)
include_directories(.)
include_directories(Lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DPLUGINS_DIR=\"${CMAKE_SOURCE_DIR}/src/plugins\")
add_definitions(-DTEST_SUITE=1)

add_subdirectory(Lib)

set(CMAKE_AUTOMOC OFF)

set(ALL_TESTS)

macro(add_mellowplayer_test TEST_TYPE TEST_ROOT_DIR)
    set(TEST_EXECUTABLE_NAME ${PROJECT_NAME}.${TEST_TYPE})
    file(GLOB_RECURSE SOURCE_FILES ${TEST_ROOT_DIR}/*.cpp)
    add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILES} main.cpp)
    target_link_libraries(${TEST_EXECUTABLE_NAME} MellowPlayer.TestsLib
                          MellowPlayer.Application MellowPlayer.Presentation MellowPlayer.Infrastructure
                          Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
                          Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets Qt5::Test)
    if (APPLE)
        add_framework(Carbon ${TEST_EXECUTABLE_NAME})
        add_framework(Cocoa ${TEST_EXECUTABLE_NAME})
    elseif(UNIX)
        find_package(X11)
        target_link_libraries(${TEST_EXECUTABLE_NAME} ${X11_LIBRARIES} Qt5::DBus)
    endif()

    if(USE_LIBNOTIFY)
        target_link_libraries(${TEST_EXECUTABLE_NAME} ${LIBNOTIFY_LIBRARIES})
    endif()

    if (LibsnoreQt5_FOUND)
        target_link_libraries(${TEST_EXECUTABLE_NAME} Snore::Libsnore)
    endif()
    add_test (NAME ${TEST_EXECUTABLE_NAME} COMMAND $<TARGET_FILE:${TEST_EXECUTABLE_NAME}>)
    set(ALL_TESTS ${ALL_TESTS} ${TEST_EXECUTABLE_NAME})
    if (USE_PRECOMPILED_HEADER)
        target_precompiled_header(${TEST_EXECUTABLE_NAME} stdafx.h)
    endif()
endmacro()

add_mellowplayer_test("Application.UnitTests" UnitTests/Application)
add_mellowplayer_test("Infrastructure.UnitTests" UnitTests/Infrastructure)
add_mellowplayer_test("Presentation.UnitTests" UnitTests/Presentation)
if (BUILD_INTEGRATION_TESTS)
    add_mellowplayer_test("Presentation.IntegrationTests" IntegrationTests/Presentation)
    add_mellowplayer_test("Infrastructure.IntegrationTests" IntegrationTests/Infrastructure)
    if (UNIX AND NOT APPLE)
        add_mellowplayer_test("MprisTests" MprisTests)
    endif()
endif()

if(${ENABLE_COVERAGE} AND ${ENABLE_LCOV_REPORT})
    setup_target_for_coverage(coverage "ctest" coverage)
endif()

add_custom_target(AllTests COMMAND ctest --output-on-failure DEPENDS ${ALL_TESTS})
