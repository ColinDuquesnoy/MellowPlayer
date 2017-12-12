set(LIB_NAME MellowPlayer.TestsLib)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${LIB_NAME}
        MellowPlayer.Domain MellowPlayer.Presentation MellowPlayer.Infrastructure
        Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
        Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets Qt5::Test
        qxtglobalshortcut)
