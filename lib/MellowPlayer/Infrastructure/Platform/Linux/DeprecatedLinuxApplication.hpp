#pragma once

#include <QObject>

#ifdef Q_OS_LINUX

#include "MellowPlayer/Infrastructure/Applications/DeprecatedCoreApplication.hpp"

namespace MellowPlayer::Domain
{
    class ILogger;
    class IDeprecatedQtApplication;
    class IMainWindow;
    class StreamingServicesController;
    class IHotkeys;
    class ISystemTrayIcon;
    class INotifier;
}

namespace MellowPlayer::Infrastructure
{
    class IMpris;

    class DeprecatedLinuxApplication : public DeprecatedCoreApplication
    {
    public:
        DeprecatedLinuxApplication(Domain::IDeprecatedQtApplication& qtApp, Domain::IMainWindow& mainWindow,
                         Domain::StreamingServicesController& streamingServices, Infrastructure::IHotkeys& kotkeys,
                         Domain::ISystemTrayIcon& systemTrayIcon, Domain::INotifier& notifier, IMpris& mprisService);
        void initialize() override;

    private:
        Domain::ILogger& logger_;
        IMpris& mpris_;
    };
}

#endif
