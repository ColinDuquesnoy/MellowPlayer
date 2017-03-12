#include "Application.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

Application::Application(IQtApplication& qtApp,
                         IMainWindow& mainWindow,
                         PluginManager& pluginManager,
                         IHotkeysService& kotkeys,
                         ISystemTrayIcon& systemTrayIcon,
                         INotificationService& notificationService) :
        logger(LoggingManager::instance().getLogger("Application")),
        qtApp(qtApp),
        mainWindow(mainWindow),
        pluginManager(pluginManager),
        kotkeys(kotkeys),
        systemTrayIcon(systemTrayIcon),
        notificationService(notificationService) {

}

void Application::initialize() {
    LOG_TRACE(logger, "initialize");
    pluginManager.load();
    mainWindow.load();
    kotkeys.start();
    notificationService.initialize();
    mainWindow.show();
    systemTrayIcon.show();
}

void Application::restoreWindow() {
    LOG_TRACE(logger, "restoreWindow");
    mainWindow.show();
}

int Application::run() {
    LOG_TRACE(logger, "run");
    return qtApp.run();
}

void Application::quit() {
    LOG_TRACE(logger, "quit");
    qtApp.quit();
}
