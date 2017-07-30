#pragma once

#include <QObject>

#ifdef Q_OS_LINUX

#include "MellowPlayer/Infrastructure/Applications/CoreApplication.hpp"

namespace MellowPlayer::Application
{
    class IQtApplication;
    class IMainWindow;
    class StreamingServicesController;
    class IHotkeysController;
    class ISystemTrayIcon;
    class INotifier;
    class IMprisController;
}

namespace MellowPlayer::Infrastructure
{
    class LinuxApplication : public CoreApplication
    {
    public:
        LinuxApplication(Application::IQtApplication& qtApp, Application::IMainWindow& mainWindow,
                         Application::StreamingServicesController& streamingServices, Application::IHotkeysController& kotkeys,
                         Application::ISystemTrayIcon& systemTrayIcon, Application::INotifier& notifier, Application::IMprisController& mprisService);
        void initialize() override;

    private:
        Application::ILogger& logger_;
        Application::IMprisController& mprisService_;
    };
}

#endif
