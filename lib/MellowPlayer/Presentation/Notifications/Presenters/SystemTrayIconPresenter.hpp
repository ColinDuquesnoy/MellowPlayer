#pragma once

#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>

namespace MellowPlayer::Presentation
{
    class ISystemTrayIcon;
    struct Notification;

    class SystemTrayIconPresenter : public INotificationPresenter
    {
    public:
        explicit SystemTrayIconPresenter(ISystemTrayIcon& systemTrayIcon);
        void initialize() override;
        bool display(const Notification& notification) override;

    private:
        ISystemTrayIcon& systemTrayIcon_;
    };
}
