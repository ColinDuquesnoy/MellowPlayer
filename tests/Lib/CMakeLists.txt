set(LIB_NAME MellowPlayer.TestsLib)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${LIB_NAME}
        MellowPlayer.Application MellowPlayer.Presentation MellowPlayer.Infrastructure
        Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
        Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets Qt5::Test)
if (qxtglobalshortcut_FOUND)
    target_link_libraries(${LIB_NAME} qxtglobalshortcut)
endif()
if (USE_PRECOMPILED_HEADER)
    set_target_properties(${LIB_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.hpp")
    set_target_properties(${LIB_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
    cotire(${LIB_NAME})
endif()