#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Application/Notifications/ISystemTrayIcon.hpp>
#include "SystemTrayIconPresenter.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

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
