#include <MellowPlayer/Domain/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Domain/IQtApplication.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Notifications/INotifier.hpp>
#include <MellowPlayer/Domain/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>

#include "CoreApplication.hpp"

using namespace MellowPlayer::Domain;
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
