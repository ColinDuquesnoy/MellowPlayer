#pragma once

#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>

namespace MellowPlayer::Application
{
    class ISystemTrayIcon;
}

namespace MellowPlayer::Presentation
{
    class SystemTrayIconPresenter : public Application::INotificationPresenter
    {
    public:
        explicit SystemTrayIconPresenter(Application::ISystemTrayIcon& systemTrayIcon);
        void initialize() override;
        bool display(const Application::Notification& notification) override;

    private:
        Application::ISystemTrayIcon& systemTrayIcon_;
    };
}
