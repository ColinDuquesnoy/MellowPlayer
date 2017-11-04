#include "LinuxApplication.hpp"
#include <MellowPlayer/Infrastructure/Hotkeys/IHotkeys.hpp>
#include <MellowPlayer/Domain/Controllers/IMprisController.hpp>
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Domain/IQtApplication.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>

#ifdef Q_OS_LINUX

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

LinuxApplication::LinuxApplication(IQtApplication& qtApp, IMainWindow& mainWindow, StreamingServicesController& streamingServices,
                                   IHotkeys& kotkeys, ISystemTrayIcon& systemTrayIcon, INotifier& notifier, IMprisController& mprisService)
        : CoreApplication(qtApp, mainWindow, streamingServices, kotkeys, systemTrayIcon, notifier),
          logger_(LoggingManager::logger("LinuxApplication")),
          mprisService_(mprisService)
{
}

void LinuxApplication::initialize()
{
    LOG_TRACE(logger_, "initialize");
    CoreApplication::initialize();
    mprisService_.start();
}

#endif