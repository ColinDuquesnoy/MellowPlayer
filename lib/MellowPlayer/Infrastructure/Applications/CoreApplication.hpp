#pragma once

#include "IApplication.hpp"

namespace MellowPlayer::Application
{
    class IQtApplication;
    class IMainWindow;
    class StreamingServicesController;
    class IHotkeysController;
    class ISystemTrayIcon;
    class INotifier;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class CoreApplication : public IApplication
    {
    public:
        CoreApplication(Application::IQtApplication& qtApp, Application::IMainWindow& mainWindow,
                        Application::StreamingServicesController& streamingServices, Application::IHotkeysController& kotkeys,
                        Application::ISystemTrayIcon& systemTrayIcon, Application::INotifier& notifier);

        void initialize() override;
        void restoreWindow() override;
        int run() override;
        void quit() override;

    private:
        Application::ILogger& logger_;
        Application::IQtApplication& qtApp_;
        Application::IMainWindow& mainWindow_;
        Application::StreamingServicesController& streamingServices_;
        Application::IHotkeysController& kotkeys_;
        Application::ISystemTrayIcon& systemTrayIcon_;
        Application::INotifier& notifier_;
    };
}
