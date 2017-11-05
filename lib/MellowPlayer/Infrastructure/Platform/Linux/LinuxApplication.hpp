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
    class IHotkeys;
    class ISystemTrayIcon;
    class INotifier;
}

namespace MellowPlayer::Infrastructure
{
    class IMpris;

    class LinuxApplication : public CoreApplication
    {
    public:
        LinuxApplication(Domain::IQtApplication& qtApp, Domain::IMainWindow& mainWindow,
                         Domain::StreamingServicesController& streamingServices, Infrastructure::IHotkeys& kotkeys,
                         Domain::ISystemTrayIcon& systemTrayIcon, Domain::INotifier& notifier, IMpris& mprisService);
        void initialize() override;

    private:
        Domain::ILogger& logger_;
        IMpris& mpris_;
    };
}

#endif
