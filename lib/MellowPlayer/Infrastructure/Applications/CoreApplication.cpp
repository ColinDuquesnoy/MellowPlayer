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

CoreApplication::CoreApplication(IQtApplication& qtApp, IMainWindow& mainWindow, StreamingServicesController& streamingServices,
                                 IHotkeysController& kotkeys, ISystemTrayIcon& systemTrayIcon, INotifier& notifier)
        : logger_(LoggingManager::logger("Application")),
          qtApp_(qtApp),
          mainWindow_(mainWindow),
          streamingServices_(streamingServices),
          kotkeys_(kotkeys),
          systemTrayIcon_(systemTrayIcon),
          notifier_(notifier)
{
}

void CoreApplication::initialize()
{
    LOG_TRACE(logger_, "initialize");
    streamingServices_.load();
    mainWindow_.load();
    kotkeys_.start();
    notifier_.initialize();
    mainWindow_.show();
    systemTrayIcon_.show();
}

void CoreApplication::restoreWindow()
{
    LOG_TRACE(logger_, "restoreWindow");
    mainWindow_.show();
}

int CoreApplication::run()
{
    LOG_TRACE(logger_, "run");
    return qtApp_.run();
}

void CoreApplication::quit()
{
    LOG_TRACE(logger_, "quit");
    qtApp_.quit();
}
