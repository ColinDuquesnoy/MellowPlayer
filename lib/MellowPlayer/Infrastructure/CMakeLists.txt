set(LIB_NAME "${PROJECT_NAME}.Infrastructure")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/core/qxtglobal.cpp
                                 ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/qxtglobalshortcut.cpp)

if (WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/win/qxtglobalshortcut_win.cpp)
elseif(APPLE)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/mac/qxtglobalshortcut_mac.cpp)
elseif(UNIX)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/x11/qxtglobalshortcut_x11.cpp)
endif()
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/core)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/spdlog-0.11.0/include/)

add_definitions(-DBUILD_QXT_CORE -DBUILD_QXT_GUI)
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
if(WIN32)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

    install(TARGETS ${LIB_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()
target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Entities ${PROJECT_NAME}.UseCases)
qt5_use_modules(${LIB_NAME} Core Widgets)
