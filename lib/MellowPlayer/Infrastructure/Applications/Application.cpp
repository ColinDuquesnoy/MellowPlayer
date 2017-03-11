#include "Application.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

Application::Application(IQtApplication& qtApp, IMainWindow& mainWindow, IHotkeysService& kotkeys,
                         ISystemTrayIcon& systemTrayIcon):
    qtApp(qtApp), mainWindow(mainWindow), kotkeys(kotkeys), systemTrayIcon(systemTrayIcon) {

}

void Application::initialize() {
    mainWindow.load();
    systemTrayIcon.show();
}

void Application::restoreWindow() {
    mainWindow.show();
}

int Application::run() {
    return qtApp.run();
}

void Application::quit() {
    qtApp.quit();
}
