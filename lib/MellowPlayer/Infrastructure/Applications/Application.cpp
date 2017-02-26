#include "Application.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

Application::Application(IQtApplication& qtApp, IMainWindow& mainWindow, IHotkeysService& kotkeys):
    qtApp(qtApp), mainWindow(mainWindow), kotkeys(kotkeys) {

}

void Application::initialize() {
    kotkeys.start();
    mainWindow.load();
}

int Application::run() {
    return qtApp.run();
}

void Application::restoreWindow() {
    mainWindow.show();
}

void Application::quit() {
    qtApp.quit();
}
