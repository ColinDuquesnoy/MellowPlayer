#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/Application/Interfaces/IQtApplication.hpp>
#include <MellowPlayer/Application/Interfaces/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/Application/Interfaces/IHotkeysService.hpp>
#include <MellowPlayer/Application/Interfaces/INotificationsService.hpp>

#include "CoreApplication.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

CoreApplication::CoreApplication(IQtApplication& qtApp,
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

void CoreApplication::initialize() {
    LOG_TRACE(logger, "initialize");
    LOG_INFO(logger, "MellowPlayer " + string(MELLOWPLAYER_VERSION))
    pluginService.load();
    mainWindow.load();
    kotkeys.start();
    notificationService.initialize();
    mainWindow.show();
    systemTrayIcon.show();
}

void CoreApplication::restoreWindow() {
    LOG_TRACE(logger, "restoreWindow");
    mainWindow.show();
}

int CoreApplication::run() {
    LOG_TRACE(logger, "run");
    return qtApp.run();
}

void CoreApplication::quit() {
    LOG_TRACE(logger, "quit");
    qtApp.quit();
}
