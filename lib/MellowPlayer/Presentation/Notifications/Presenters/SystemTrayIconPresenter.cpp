#include "SystemTrayIconPresenter.hpp"
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

SystemTrayIconPresenter::SystemTrayIconPresenter(ISystemTrayIcon& systemTrayIcon) : systemTrayIcon(systemTrayIcon)
{
}

bool SystemTrayIconPresenter::display(const Notification& notification)
{
    systemTrayIcon.showMessage(notification.title, notification.description);
    return true;
}

void SystemTrayIconPresenter::initialize()
{
    systemTrayIcon.show();
}
