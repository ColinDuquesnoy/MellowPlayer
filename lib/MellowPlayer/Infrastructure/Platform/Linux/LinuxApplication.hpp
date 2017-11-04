#pragma once

#include <QObject>

#ifdef Q_OS_LINUX

#include "MellowPlayer/Infrastructure/Applications/CoreApplication.hpp"

namespace MellowPlayer::Domain
{
    class ILogger;
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
        LinuxApplication(Domain::IQtApplication& qtApp, Domain::IMainWindow& mainWindow,
                         Domain::StreamingServicesController& streamingServices, Domain::IHotkeysController& kotkeys,
                         Domain::ISystemTrayIcon& systemTrayIcon, Domain::INotifier& notifier, Domain::IMprisController& mprisService);
        void initialize() override;

    private:
        Domain::ILogger& logger_;
        Domain::IMprisController& mprisService_;
    };
}

#endif
