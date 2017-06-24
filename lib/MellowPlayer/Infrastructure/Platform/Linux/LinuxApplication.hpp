#pragma once

#ifdef Q_OS_LINUX

#include "MellowPlayer/Infrastructure/Applications/CoreApplication.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServices)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IHotkeysController)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ISystemTrayIcon)
PREDECLARE_MELLOWPLAYER_CLASS(Application, INotifier)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMprisController)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LinuxApplication: public CoreApplication {
public:
    LinuxApplication(Application::IQtApplication& qtApp,
                     Application::IMainWindow& mainWindow,
                     Application::StreamingServices& streamingServices,
                     Application::IHotkeysController& kotkeys,
                     Application::ISystemTrayIcon& systemTrayIcon,
                     Application::INotifier& notifier,
                     Application::IMprisController& mprisService);
    void initialize() override;

private:
    Application::ILogger& logger;
    Application::IMprisController& mprisService;
};

END_MELLOWPLAYER_NAMESPACE

#endif
