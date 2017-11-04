#include "SystemTrayIconPresenter.hpp"
#include <MellowPlayer/Domain/Notifications/ISystemTrayIcon.hpp>
#include <MellowPlayer/Domain/Notifications/Notifications.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
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
