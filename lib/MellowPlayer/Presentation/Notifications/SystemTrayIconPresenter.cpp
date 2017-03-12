#include "SystemTrayIconPresenter.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SystemTrayIconPresenter::SystemTrayIconPresenter(ISystemTrayIcon& systemTrayIcon):
        systemTrayIcon(systemTrayIcon) {

}

void SystemTrayIconPresenter::display(const Notification& notification) {
    systemTrayIcon.showMessage(notification.title, notification.description);
}

void SystemTrayIconPresenter::initialize() {
    systemTrayIcon.show();
}
