#include <MellowPlayer/Application/Presentation/IQtApplication.hpp>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "LinuxApplication.hpp"

#ifdef Q_OS_LINUX

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

LinuxApplication::LinuxApplication(IQtApplication& qtApp,
                                   IMainWindow& mainWindow,
                                   StreamingServices& streamingServices,
                                   IHotkeysController& kotkeys,
                                   ISystemTrayIcon& systemTrayIcon,
                                   INotifier& notifier,
                                   IMprisController& mprisService) :
        CoreApplication(qtApp, mainWindow, streamingServices, kotkeys, systemTrayIcon, notifier),
        logger(LoggingManager::instance().getLogger("LinuxApplication")),
        mprisService(mprisService) {

}

void LinuxApplication::initialize() {
    LOG_TRACE(logger, "initialize");
    CoreApplication::initialize();
    mprisService.start();
}

#endif