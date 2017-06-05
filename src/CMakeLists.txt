file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/lib/*.hpp)

# plugins files (include them as source to be able to see them in QtCreator)
set(CMAKE_AUTOMOC OFF)

add_definitions(-DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)

add_executable(${PROJECT_NAME} main.cpp DI.hpp)
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

if (LibsnoreQt5_FOUND)
    target_link_libraries(${PROJECT_NAME} Snore::Libsnore)
endif()

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static)
