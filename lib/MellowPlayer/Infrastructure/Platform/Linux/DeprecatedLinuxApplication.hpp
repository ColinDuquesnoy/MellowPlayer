#pragma once

#include <QObject>

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)

#include "MellowPlayer/Infrastructure/Applications/DeprecatedCoreApplication.hpp"

namespace MellowPlayer::Domain
{
    class ILogger;
    class IDeprecatedQtApplication;
    class IDeprecatedMainWindow;
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
        DeprecatedLinuxApplication(Domain::IDeprecatedQtApplication& qtApp, Domain::IDeprecatedMainWindow& mainWindow,
                         Domain::StreamingServicesController& streamingServices, Infrastructure::IHotkeys& kotkeys,
                         Domain::ISystemTrayIcon& systemTrayIcon, Domain::INotifier& notifier, IMpris& mprisService);
        void initialize() override;

    private:
        Domain::ILogger& logger_;
        IMpris& mpris_;
    };
}

#endif
