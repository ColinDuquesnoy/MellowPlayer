#include <MellowPlayer/Application/Interfaces/IQtApplication.hpp>
#include <MellowPlayer/Application/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include <MellowPlayer/Application/Interfaces/IHotkeysService.hpp>
#include <MellowPlayer/Application/Interfaces/IMprisService.hpp>
#include <MellowPlayer/Application/Interfaces/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "LinuxApplication.hpp"

#ifdef Q_OS_LINUX

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

LinuxApplication::LinuxApplication(IQtApplication& qtApp,
                                   IMainWindow& mainWindow,
                                   StreamingServicePluginService& pluginService,
                                   IHotkeysService& kotkeys,
                                   ISystemTrayIcon& systemTrayIcon,
                                   INotificationService& playerNotificationService,
                                   IMprisService& mprisService) :
        CoreApplication(qtApp, mainWindow, pluginService, kotkeys, systemTrayIcon, playerNotificationService),
        logger(LoggingManager::instance().getLogger("LinuxApplication")),
        mprisService(mprisService) {

}

void LinuxApplication::initialize() {
    LOG_TRACE(logger, "initialize");
    CoreApplication::initialize();
    mprisService.start();
}

#endif