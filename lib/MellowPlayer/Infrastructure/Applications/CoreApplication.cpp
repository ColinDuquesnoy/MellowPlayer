#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Application/Presentation/IQtApplication.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/Notifications/INotifier.hpp>

#include "CoreApplication.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

CoreApplication::CoreApplication(IQtApplication& qtApp,
                           IMainWindow& mainWindow,
                           StreamingServices& streamingServices,
                           IHotkeysController& kotkeys,
                           ISystemTrayIcon& systemTrayIcon,
                           INotifier& notifier) :
        logger(LoggingManager::instance().getLogger("Application")),
        qtApp(qtApp),
        mainWindow(mainWindow),
        streamingServices(streamingServices),
        kotkeys(kotkeys),
        systemTrayIcon(systemTrayIcon),
        notifier(notifier) {

}

void CoreApplication::initialize() {
    LOG_TRACE(logger, "initialize");
    LOG_INFO(logger, "MellowPlayer " + string(MELLOWPLAYER_VERSION))
    streamingServices.load();
    mainWindow.load();
    kotkeys.start();
    notifier.initialize();
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
