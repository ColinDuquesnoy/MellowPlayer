#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ISystemTrayIcon)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SystemTrayIconPresenter: public Application::INotificationPresenter {
public:
    SystemTrayIconPresenter(Application::ISystemTrayIcon& systemTrayIcon);
    void initialize() override;
    bool display(const Application::Notification& notification) override;

private:
    Application::ISystemTrayIcon& systemTrayIcon;
};

END_MELLOWPLAYER_NAMESPACE
