#pragma once

#include <MellowPlayer/Domain/Notifications/INotificationPresenter.hpp>

namespace MellowPlayer::Domain
{
    class ISystemTrayIcon;
    struct Notification;
}

namespace MellowPlayer::Presentation
{
    class SystemTrayIconPresenter : public Domain::INotificationPresenter
    {
    public:
        explicit SystemTrayIconPresenter(Domain::ISystemTrayIcon& systemTrayIcon);
        void initialize() override;
        bool display(const Domain::Notification& notification) override;

    private:
        Domain::ISystemTrayIcon& systemTrayIcon_;
    };
}
