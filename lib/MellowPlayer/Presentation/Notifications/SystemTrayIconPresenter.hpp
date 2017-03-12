#pragma once

#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SystemTrayIconPresenter: public UseCases::INotificationPresenter {
public:
    SystemTrayIconPresenter(UseCases::ISystemTrayIcon& systemTrayIcon);
    void initialize() override;
    void display(const UseCases::Notification& notification) override;

private:
    UseCases::ISystemTrayIcon& systemTrayIcon;
};

END_MELLOWPLAYER_NAMESPACE
