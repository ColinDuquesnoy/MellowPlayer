#pragma once

#include "IApplication.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingServicesController)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IHotkeysController)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ISystemTrayIcon)
PREDECLARE_MELLOWPLAYER_CLASS(Application, INotifier)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)


BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class CoreApplication : public IApplication {
public:
    CoreApplication(Application::IQtApplication& qtApp,
                    Application::IMainWindow& mainWindow,
                    Application::StreamingServicesController& streamingServices,
                    Application::IHotkeysController& kotkeys,
                    Application::ISystemTrayIcon& systemTrayIcon,
                    Application::INotifier& notifier);

    void initialize() override;
    void restoreWindow() override;
    int run() override;
    void quit() override;

private:
    Application::ILogger& logger;
    Application::IQtApplication& qtApp;
    Application::IMainWindow& mainWindow;
    Application::StreamingServicesController& streamingServices;
    Application::IHotkeysController& kotkeys;
    Application::ISystemTrayIcon& systemTrayIcon;
    Application::INotifier& notifier;
};

END_MELLOWPLAYER_NAMESPACE
