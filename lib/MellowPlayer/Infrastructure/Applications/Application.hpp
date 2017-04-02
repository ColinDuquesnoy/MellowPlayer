#pragma once

#include "IApplication.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, PluginManager)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IHotkeysService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ISystemTrayIcon)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, INotificationService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)


BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Application : public IApplication {
public:
    Application(UseCases::IQtApplication& qtApp,
                UseCases::IMainWindow& mainWindow,
                UseCases::PluginManager& pluginManager,
                UseCases::IHotkeysService& kotkeys,
                UseCases::ISystemTrayIcon& systemTrayIcon,
                UseCases::INotificationService& notificationService);

    void initialize() override;
    void restoreWindow() override;
    int run() override;
    void quit() override;

private:
    UseCases::ILogger& logger;
    UseCases::IQtApplication& qtApp;
    UseCases::IMainWindow& mainWindow;
    UseCases::PluginManager& pluginManager;
    UseCases::IHotkeysService& kotkeys;
    UseCases::ISystemTrayIcon& systemTrayIcon;
    UseCases::INotificationService& notificationService;
};

END_MELLOWPLAYER_NAMESPACE
