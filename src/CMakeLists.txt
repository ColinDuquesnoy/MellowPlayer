file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/lib/*.hpp)
add_executable(${PROJECT_NAME} main.cpp main.qrc qml/main.qml qtquickcontrols2.conf ${HEADER_FILES})
qt5_use_modules(${PROJECT_NAME} Core Gui Quick QuickControls2 WebEngine)
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}.Entities
        ${PROJECT_NAME}.UseCases
        ${PROJECT_NAME}.Infrastructure
        ${PROJECT_NAME}.Presentation)
