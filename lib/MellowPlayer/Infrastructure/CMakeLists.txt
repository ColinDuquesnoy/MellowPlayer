include(${CMAKE_SOURCE_DIR}/scripts/cmake/Macros.cmake)

set(LIB_NAME "${PROJECT_NAME}.Infrastructure")

glob_recurse_excl(SOURCE_FILES *.cpp "Platform")
glob_recurse_excl(HEADER_FILES *.hpp "Platform")

set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/qxtglobalshortcut.cpp)
if (WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/win/qxtglobalshortcut_win.cpp)
elseif(APPLE)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/mac/qxtglobalshortcut_mac.cpp)
elseif(UNIX)
    file(GLOB_RECURSE LINUX_SOURCE_FILES Platform/Linux/*.cpp)
    file(GLOB_RECURSE LINUX_HEADER_FILES Platform/Linux/*.hpp)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/x11/qxtglobalshortcut_x11.cpp)
    set(SOURCE_FILES ${SOURCE_FILES} ${LINUX_SOURCE_FILES})
    set(HEADER_FILES ${HEADER_FILES} ${LINUX_HEADER_FILES})
endif()
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/core)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/spdlog-0.11.0/include/)

add_definitions(-DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Application)
qt5_use_modules(${LIB_NAME} Concurrent Core Widgets Network Sql)

if(UNIX AND NOT APPLE)
    qt5_use_modules(${LIB_NAME} DBus)
endif()

