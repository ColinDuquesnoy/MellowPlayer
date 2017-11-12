#pragma once

#include "IDeprecatedApplication.hpp"

namespace MellowPlayer::Domain
{
    class IDeprecatedQtApplication;
    class IMainWindow;
    class StreamingServicesController;
    class ISystemTrayIcon;
    class INotifier;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class IHotkeys;

    class DeprecatedCoreApplication : public IDeprecatedApplication
    {
    public:
        DeprecatedCoreApplication(Domain::IDeprecatedQtApplication& qtApp, Domain::IMainWindow& mainWindow,
                        Domain::StreamingServicesController& streamingServices, IHotkeys& kotkeys,
                        Domain::ISystemTrayIcon& systemTrayIcon, Domain::INotifier& notifier);

        void initialize() override;
        void restoreWindow() override;
        int run() override;
        void quit() override;

    private:
        Domain::ILogger& logger_;
        Domain::IDeprecatedQtApplication& qtApp_;
        Domain::IMainWindow& mainWindow_;
        Domain::StreamingServicesController& streamingServices_;
        IHotkeys& kotkeys_;
        Domain::ISystemTrayIcon& systemTrayIcon_;
        Domain::INotifier& notifier_;
    };
}
