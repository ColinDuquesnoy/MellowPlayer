add_executable(${PROJECT_NAME} main.cpp main.qrc qml/main.qml qtquickcontrols2.conf)
qt5_use_modules(${PROJECT_NAME} Core Gui Quick QuickControls2 WebEngine)
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}.Entities
        ${PROJECT_NAME}.UseCases
        ${PROJECT_NAME}.Infrastructure
        ${PROJECT_NAME}.QmlFrontend)
