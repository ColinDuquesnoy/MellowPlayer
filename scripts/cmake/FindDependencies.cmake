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
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Concurren_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5Qml_INCLUDE_DIRS})
include_directories(${Qt5Quick_INCLUDE_DIRS})
include_directories(${Qt5QuickControls2_INCLUDE_DIRS})
include_directories(${Qt5Sql_INCLUDE_DIRS})
include_directories(${Qt5Svg_INCLUDE_DIRS})
include_directories(${Qt5Test_INCLUDE_DIRS})
include_directories(${Qt5WebEngine_INCLUDE_DIRS})
include_directories(${Qt5WebEngineWidgets_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})


if (UNIX AND NOT APPLE)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus)
    include_directories(${QtDBus_INCLUDE_DIRS})
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
