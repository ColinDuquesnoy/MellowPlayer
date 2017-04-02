#include <MellowPlayer/UseCases/Interfaces/ISystemTrayIcon.hpp>
#include <MellowPlayer/UseCases/Notifications/Notifications.hpp>
#include "SystemTrayIconPresenter.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
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
