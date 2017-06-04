#include <libnotify/notify.h>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "LibnotifyPresenter.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

LibnotifyPresenter* LibnotifyPresenter::instance = nullptr;

void notify_action_callback(NotifyNotification*, char*, gpointer) { LibnotifyPresenter::onActionCallback(); }

LibnotifyPresenter::LibnotifyPresenter(IMainWindow& mainWindow) :
        logger(LoggingManager::instance().getLogger("LibnotifyPresenter")),
        mainWindow(mainWindow),
        previousNotification(nullptr) {
    instance = this;
}

void LibnotifyPresenter::initialize() {
    notify_init("MellowPlayer");
    LOG_INFO(logger, "service started")
}

bool LibnotifyPresenter::display(const Notification& notification) {
    if (previousNotification)
        notify_notification_close(previousNotification, 0);
    QString title = "MellowPlayer - " + notification.title;
    NotifyNotification* n = notify_notification_new(title.toStdString().c_str(),
                                                    notification.description.toStdString().c_str(),
                                                    notification.icon.toStdString().c_str());
    notify_notification_set_timeout(n, 5000);
    notify_notification_add_action(n, "open", "Open", (NotifyActionCallback) notify_action_callback, nullptr, nullptr);
    bool success = static_cast<bool>(notify_notification_show(n, 0));
    previousNotification = n;
    return success;
}

void LibnotifyPresenter::onActionCallback() {
    instance->mainWindow.show();
}
