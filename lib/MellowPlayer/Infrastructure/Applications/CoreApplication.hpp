#pragma once

#include "IApplication.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServicePluginService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IHotkeysService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ISystemTrayIcon)
PREDECLARE_MELLOWPLAYER_CLASS(Application, INotificationService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)


BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class CoreApplication : public IApplication {
public:
    CoreApplication(Application::IQtApplication& qtApp,
                    Application::IMainWindow& mainWindow,
                    Application::StreamingServicePluginService& pluginService,
                    Application::IHotkeysService& kotkeys,
                    Application::ISystemTrayIcon& systemTrayIcon,
                    Application::INotificationService& notificationService);

    void initialize() override;
    void restoreWindow() override;
    int run() override;
    void quit() override;

private:
    Application::ILogger& logger;
    Application::IQtApplication& qtApp;
    Application::IMainWindow& mainWindow;
    Application::StreamingServicePluginService& pluginService;
    Application::IHotkeysService& kotkeys;
    Application::ISystemTrayIcon& systemTrayIcon;
    Application::INotificationService& notificationService;
};

END_MELLOWPLAYER_NAMESPACE
