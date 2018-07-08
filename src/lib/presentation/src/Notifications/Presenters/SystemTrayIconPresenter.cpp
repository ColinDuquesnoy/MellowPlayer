#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Presentation/Notifications/Notification.hpp>

using namespace MellowPlayer::Presentation;

SystemTrayIconPresenter::SystemTrayIconPresenter(ISystemTrayIcon& systemTrayIcon) : systemTrayIcon_(systemTrayIcon)
{
}

bool SystemTrayIconPresenter::display(const Notification& notification)
{
    systemTrayIcon_.showMessage(notification.title, notification.description);
    return true;
}

void SystemTrayIconPresenter::initialize()
{
    systemTrayIcon_.show();
}
