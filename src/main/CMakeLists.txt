add_executable(${PROJECT_NAME} main.cpp main.qrc qml/main.qml qtquickcontrols2.conf)
qt5_use_modules(${PROJECT_NAME} Core Gui Quick QuickControls2)
