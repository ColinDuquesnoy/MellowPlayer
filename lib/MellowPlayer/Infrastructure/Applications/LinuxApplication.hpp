#pragma once

#ifdef Q_OS_LINUX

#include "Application.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PluginService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IHotkeysService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ISystemTrayIcon)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, INotificationService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IMprisService)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LinuxApplication: public Application {
public:
    LinuxApplication(UseCases::IQtApplication& qtApp,
                     UseCases::IMainWindow& mainWindow,
                     UseCases::PluginService& pluginService,
                     UseCases::IHotkeysService& kotkeys,
                     UseCases::ISystemTrayIcon& systemTrayIcon,
                     UseCases::INotificationService& playerNotificationService,
                     UseCases::IMprisService& mprisService);
    void initialize() override;

private:
    UseCases::ILogger& logger;
    UseCases::IMprisService& mprisService;
};

END_MELLOWPLAYER_NAMESPACE

#endif
