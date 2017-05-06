#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Interfaces/INotificationPresenter.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ISystemTrayIcon)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SystemTrayIconPresenter: public UseCases::INotificationPresenter {
public:
    SystemTrayIconPresenter(UseCases::ISystemTrayIcon& systemTrayIcon);
    void initialize() override;
    bool display(const Entities::Notification& notification) override;

private:
    UseCases::ISystemTrayIcon& systemTrayIcon;
};

END_MELLOWPLAYER_NAMESPACE
