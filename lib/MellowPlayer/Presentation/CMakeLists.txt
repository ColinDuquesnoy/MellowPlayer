set(LIB_NAME "${PROJECT_NAME}.Presentation")

glob_recurse_excl(HEADER_FILES *.hpp "Presenters")
glob_recurse_excl(SOURCE_FILES *.cpp "Presenters")
file(GLOB_RECURSE QML_FILES Views/*.qml)
file(GLOB_RECURSE QRC_FILES *.qrc)
file(GLOB_RECURSE CONF_FILES *.conf)

set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/Views ${CMAKE_SOURCE_DIR}/Views/MellowPlayer CACHE string "" FORCE)

if(USE_LIBNOTIFY)
    include_directories(${LIBNOTIFY_INCLUDE_DIRS})
endif()

set(QML_FILES ${QML_FILES} Views/MellowPlayer/qmldir)

set(SOURCE_FILES ${SOURCE_FILES} Notifications/Presenters/SystemTrayIconPresenter.cpp)
set(HEADER_FILES ${HEADER_FILES} Notifications/Presenters/SystemTrayIconPresenter.hpp)
if(USE_LIBNOTIFY)
    set(SOURCE_FILES ${SOURCE_FILES} Notifications/Presenters/LibnotifyPresenter.cpp)
    set(HEADER_FILES ${HEADER_FILES} Notifications/Presenters/LibnotifyPresenter.hpp)
endif()

SET(CMAKE_DEBUG_POSTFIX "")
add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES} ${QML_FILES} ${CONF_FILES})
target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Application)
qt5_use_modules(${LIB_NAME} Core Qml Quick WebEngine WebEngineWidgets Widgets QuickControls2 Svg)
