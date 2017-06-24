file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/lib/*.hpp)

# plugins files (include them as source to be able to see them in QtCreator)
set(CMAKE_AUTOMOC OFF)

add_definitions(-DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)


set(SOURCE_FILES main.cpp DI.hpp)

if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} MellowPlayer.rc)
    configure_file(../scripts/packaging/windows/setup_templ.iss ${CMAKE_BINARY_DIR}/setup.iss)
endif()

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32 ${SOURCE_FILES})

if (WIN32)
    # add a console based executable for easier debugging
    add_executable(${PROJECT_NAME}.Console MACOSX_BUNDLE ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME}.Console
                          ${PROJECT_NAME}.Application
                          ${PROJECT_NAME}.Presentation
                          ${PROJECT_NAME}.Infrastructure)
    qt5_use_modules(${PROJECT_NAME}.Console Concurrent Core Qml Quick WebEngine WebEngineWidgets Widgets QuickControls2 Network Sql)
endif()

include_directories(../3rdparty)
target_link_libraries(${PROJECT_NAME}
                      ${PROJECT_NAME}.Application
                      ${PROJECT_NAME}.Presentation
                      ${PROJECT_NAME}.Infrastructure)
qt5_use_modules(${PROJECT_NAME} Concurrent Core Qml Quick WebEngine WebEngineWidgets Widgets QuickControls2 Network Sql)

if (APPLE)
    add_framework(Carbon ${PROJECT_NAME})
    add_framework(Cocoa ${PROJECT_NAME})
elseif(UNIX)
    qt5_use_modules(${PROJECT_NAME} DBus)
    find_package(X11)
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
    if (STATIC_LIBSTDCPP)
        message(WARNING "Linking statically to libgcc and libstdc++")
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    endif()
endif()

if(USE_LIBNOTIFY)
    target_link_libraries(${PROJECT_NAME} ${LIBNOTIFY_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION MacOS
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static)
