#pragma once

#ifdef Q_OS_LINUX

#include "CoreApplication.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServicePluginService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IHotkeysService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ISystemTrayIcon)
PREDECLARE_MELLOWPLAYER_CLASS(Application, INotificationService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMprisService)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LinuxApplication: public CoreApplication {
public:
    LinuxApplication(Application::IQtApplication& qtApp,
                     Application::IMainWindow& mainWindow,
                     Application::StreamingServicePluginService& pluginService,
                     Application::IHotkeysService& kotkeys,
                     Application::ISystemTrayIcon& systemTrayIcon,
                     Application::INotificationService& playerNotificationService,
                     Application::IMprisService& mprisService);
    void initialize() override;

private:
    Application::ILogger& logger;
    Application::IMprisService& mprisService;
};

END_MELLOWPLAYER_NAMESPACE

#endif
