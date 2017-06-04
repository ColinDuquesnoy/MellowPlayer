#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include "SystemTrayIconPresenter.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SystemTrayIconPresenter::SystemTrayIconPresenter(ISystemTrayIcon& systemTrayIcon):
        systemTrayIcon(systemTrayIcon) {

}

bool SystemTrayIconPresenter::display(const Notification& notification) {
    systemTrayIcon.showMessage(notification.title, notification.description);
    return true;
}

void SystemTrayIconPresenter::initialize() {
    systemTrayIcon.show();
}
