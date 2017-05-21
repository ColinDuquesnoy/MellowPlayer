#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/UseCases/Interfaces/IQtApplication.hpp>
#include <MellowPlayer/UseCases/Interfaces/ISystemTrayIcon.hpp>
#include <MellowPlayer/UseCases/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/UseCases/Interfaces/IHotkeysService.hpp>
#include <MellowPlayer/UseCases/Interfaces/INotificationsService.hpp>

#include "Application.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

Application::Application(IQtApplication& qtApp,
                         IMainWindow& mainWindow,
                         StreamingServicePluginService& pluginService,
                         IHotkeysService& kotkeys,
                         ISystemTrayIcon& systemTrayIcon,
                         INotificationService& notificationService) :
        logger(LoggingManager::instance().getLogger("Application")),
        qtApp(qtApp),
        mainWindow(mainWindow),
        pluginService(pluginService),
        kotkeys(kotkeys),
        systemTrayIcon(systemTrayIcon),
        notificationService(notificationService) {

}

void Application::initialize() {
    LOG_TRACE(logger, "initialize");
    LOG_INFO(logger, "MellowPlayer " + string(MELLOWPLAYER_VERSION))
    pluginService.load();
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
