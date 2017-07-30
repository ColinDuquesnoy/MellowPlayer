#include "LinuxApplication.hpp"
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/IQtApplication.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>

#ifdef Q_OS_LINUX

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

LinuxApplication::LinuxApplication(IQtApplication& qtApp, IMainWindow& mainWindow, StreamingServicesController& streamingServices,
                                   IHotkeysController& kotkeys, ISystemTrayIcon& systemTrayIcon, INotifier& notifier, IMprisController& mprisService)
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