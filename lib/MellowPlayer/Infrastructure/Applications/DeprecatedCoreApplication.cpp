#include <MellowPlayer/Infrastructure/Hotkeys/IHotkeys.hpp>
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Domain/IDeprecatedQtApplication.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Notifications/INotifier.hpp>
#include <MellowPlayer/Domain/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>

#include "DeprecatedCoreApplication.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

DeprecatedCoreApplication::DeprecatedCoreApplication(IDeprecatedQtApplication& qtApp, IMainWindow& mainWindow, StreamingServicesController& streamingServices,
                                 IHotkeys& kotkeys, ISystemTrayIcon& systemTrayIcon, INotifier& notifier)
        : logger_(LoggingManager::logger("Application")),
          qtApp_(qtApp),
          mainWindow_(mainWindow),
          streamingServices_(streamingServices),
          kotkeys_(kotkeys),
          systemTrayIcon_(systemTrayIcon),
          notifier_(notifier)
{
}

void DeprecatedCoreApplication::initialize()
{
    LOG_TRACE(logger_, "initialize");
    streamingServices_.load();
    mainWindow_.load();
    kotkeys_.start();
    notifier_.initialize();
    mainWindow_.show();
    systemTrayIcon_.show();
}

void DeprecatedCoreApplication::restoreWindow()
{
    LOG_TRACE(logger_, "restoreWindow");
    mainWindow_.show();
}

int DeprecatedCoreApplication::run()
{
    LOG_TRACE(logger_, "run");
    return qtApp_.run();
}

void DeprecatedCoreApplication::quit()
{
    LOG_TRACE(logger_, "quit");
    qtApp_.quit();
}
