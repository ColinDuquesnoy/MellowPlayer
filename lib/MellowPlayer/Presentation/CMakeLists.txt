set(LIB_NAME "${PROJECT_NAME}.Presentation")

glob_recurse_excl(HEADER_FILES *.hpp "Presenters")
glob_recurse_excl(SOURCE_FILES *.cpp "Presenters")
file(GLOB_RECURSE QML_FILES Views/*.qml)
file(GLOB_RECURSE QRC_FILES *.qrc)
file(GLOB_RECURSE CONF_FILES *.conf)

set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/qt-qml-models/QQmlObjectListModel.cpp)
set(HEADER_FILES ${HEADER_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/qt-qml-models/QQmlObjectListModel.hpp)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/qt-qml-models)

set(QML_FILES ${QML_FILES} Views/MellowPlayer/qmldir)

set(SOURCE_FILES ${SOURCE_FILES} Notifications/Presenters/SystemTrayIconPresenter.cpp)
set(HEADER_FILES ${HEADER_FILES} Notifications/Presenters/SystemTrayIconPresenter.hpp)
if(USE_LIBNOTIFY)
    set(SOURCE_FILES ${SOURCE_FILES} Notifications/Presenters/LibnotifyPresenter.cpp)
    set(HEADER_FILES ${HEADER_FILES} Notifications/Presenters/LibnotifyPresenter.hpp)
elseif(LibsnoreQt5_FOUND)
    set(SOURCE_FILES ${SOURCE_FILES} Notifications/Presenters/SnorenotifyPresenter.cpp)
    set(HEADER_FILES ${HEADER_FILES} Notifications/Presenters/SnorenotifyPresenter.hpp)
endif()

SET(CMAKE_DEBUG_POSTFIX "")
if(WIN32)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES} ${QML_FILES} ${CONF_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES} ${QML_FILES} ${CONF_FILES})
    target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Application)
    install(TARGETS ${LIB_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static)
endif()

if(USE_LIBNOTIFY)
    include_directories(${LIBNOTIFY_INCLUDE_DIRS})
    target_link_libraries(${LIB_NAME} ${LIBNOTIFY_LIBRARIES})
endif()

if (LibsnoreQt5_FOUND)
    target_link_libraries(${LIB_NAME} Snore::Libsnore)
endif()


qt5_use_modules(${LIB_NAME} Core Qml Quick WebEngine WebEngineWidgets Widgets QuickControls2)
