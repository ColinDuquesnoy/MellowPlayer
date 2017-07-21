#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/IQtApplication.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Notifications/INotifier.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>

#include "CoreApplication.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace std;

CoreApplication::CoreApplication(IQtApplication &qtApp, IMainWindow &mainWindow, StreamingServicesController &streamingServices,
                                 IHotkeysController &kotkeys, ISystemTrayIcon &systemTrayIcon, INotifier &notifier)
        : logger(LoggingManager::instance().getLogger("Application")),
          qtApp(qtApp),
          mainWindow(mainWindow),
          streamingServices(streamingServices),
          kotkeys(kotkeys),
          systemTrayIcon(systemTrayIcon),
          notifier(notifier)
{
}

void CoreApplication::initialize()
{
    LOG_TRACE(logger, "initialize");
    streamingServices.load();
    mainWindow.load();
    kotkeys.start();
    notifier.initialize();
    mainWindow.show();
    systemTrayIcon.show();
}

void CoreApplication::restoreWindow()
{
    LOG_TRACE(logger, "restoreWindow");
    mainWindow.show();
}

int CoreApplication::run()
{
    LOG_TRACE(logger, "run");
    return qtApp.run();
}

void CoreApplication::quit()
{
    LOG_TRACE(logger, "quit");
    qtApp.quit();
}
