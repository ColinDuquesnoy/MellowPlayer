set(LIB_NAME "${PROJECT_NAME}.Infrastructure")

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)
file(GLOB APPLICATIONS_SOURCE_FILES Applications/*.cpp)
file(GLOB APPLICATIONS_HEADER_FILES Applications/*.hpp)
file(GLOB LOGGING_SOURCE_FILES Logging/*.cpp)
file(GLOB LOGGING_HEADER_FILES Logging/*.hpp)
file(GLOB MPRIS_SOURCE_FILES Services/Mpris/*.cpp)
file(GLOB MPRIS_HEADER_FILES Services/Mpris/*.hpp)
file(GLOB SERVICES_SOURCE_FILES Services/*.cpp)
file(GLOB SERVICES_HEADER_FILES Services/*.hpp)
file(GLOB SYSTEM_SOURCE_FILES System/*.cpp)
file(GLOB SYSTEM_HEADER_FILES System/*.hpp)

set(SOURCE_FILES ${SOURCE_FILES}
        ${LOGGING_SOURCE_FILES} ${SYSTEM_SOURCE_FILES} ${APPLICATIONS_SOURCE_FILES} ${SERVICES_SOURCE_FILES})
set(HEADER_FILES ${HEADER_FILES}
        ${LOGGING_HEADER_FILES} ${SYSTEM_HEADER_FILES} ${APPLICATIONS_HEADER_FILES} ${SERVICES_HEADER_FILES})

set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/core/qxtglobal.cpp
                                 ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/qxtglobalshortcut.cpp)

if (WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/win/qxtglobalshortcut_win.cpp)
elseif(APPLE)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/mac/qxtglobalshortcut_mac.cpp)
elseif(UNIX)
    set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/x11/qxtglobalshortcut_x11.cpp)
    set(SOURCE_FILES ${SOURCE_FILES} ${MPRIS_SOURCE_FILES})
    set(HEADER_FILES ${HEADER_FILES} ${MPRIS_HEADER_FILES} ApplicationSettings.cpp ApplicationSettings.hpp)
endif()
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/core)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/libqxt/src/widgets/)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/spdlog-0.11.0/include/)

add_definitions(-DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
if(WIN32)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
    target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.UseCases)
    install(TARGETS ${LIB_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()
qt5_use_modules(${LIB_NAME} Core Widgets Network)

if(UNIX AND NOT APPLE)
    qt5_use_modules(${LIB_NAME} DBus)
endif()