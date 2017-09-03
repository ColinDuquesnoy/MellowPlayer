set(QT_MIN_VERSION 5.9)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
             Concurrent
             Core
             Gui
             Network
             Qml
             Quick
             QuickControls2
             Sql
             Svg
             Test
             WebEngine
             WebEngineWidgets
             Widgets)
find_package(Qt5LinguistTools REQUIRED)

if (UNIX AND NOT APPLE)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
message(STATUS "Found Qt ${Qt5_VERSION} in ${Qt5_DIR}")

if(USE_LIBNOTIFY)
    find_package(PkgConfig)
    pkg_search_module(LIBNOTIFY REQUIRED libnotify)
    if (LIBNOTIFY_FOUND)
        message(STATUS "Found libnotify ${LIBNOTIFY_VERSION}")
        add_definitions(-DUSE_LIBNOTIFY)
    else ()
        message(STATUS "libnotify not found, system tray icon based notifications will be enabled")
    endif()
endif()

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "ccache enabled")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

