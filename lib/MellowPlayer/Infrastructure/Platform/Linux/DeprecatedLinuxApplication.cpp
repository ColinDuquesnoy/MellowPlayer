#include "DeprecatedLinuxApplication.hpp"
#include <MellowPlayer/Infrastructure/Hotkeys/IHotkeys.hpp>
#include <MellowPlayer/Infrastructure/Platform/Linux/IMpris.hpp>
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <MellowPlayer/Domain/IDeprecatedQtApplication.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

DeprecatedLinuxApplication::DeprecatedLinuxApplication(IDeprecatedQtApplication& qtApp, IMainWindow& mainWindow, StreamingServicesController& streamingServices,
                                   IHotkeys& kotkeys, ISystemTrayIcon& systemTrayIcon, INotifier& notifier, IMpris& mprisService)
        : DeprecatedCoreApplication(qtApp, mainWindow, streamingServices, kotkeys, systemTrayIcon, notifier),
          logger_(LoggingManager::logger("LinuxApplication")),
          mpris_(mprisService)
{
}

void DeprecatedLinuxApplication::initialize()
{
    LOG_TRACE(logger_, "initialize");
    DeprecatedCoreApplication::initialize();
    mpris_.start();
}

#endif