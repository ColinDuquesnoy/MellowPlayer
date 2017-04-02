#include "ApplicationSettings.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

const QString ApplicationSettings::CURRENT_SERVICE_KEY = "currentService";
const QString ApplicationSettings::SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY = "showCloseToSystemTrayMessage";
const QString ApplicationSettings::TRAY_ICON_KEY = "getTrayIcon";
const QString ApplicationSettings::NOTIFICATIONS_ENABLED_KEY = "notificationsEnabled";
const QString ApplicationSettings::NOTIFICATION_ENABLED_KEY = "notification/%1";

ApplicationSettings::ApplicationSettings(): qSettings() {

}

void ApplicationSettings::clear() {
    qSettings.clear();
}

QString ApplicationSettings::getCurrentService() const {
    return qSettings.value(CURRENT_SERVICE_KEY, "").toString();
}

void ApplicationSettings::setCurrentService(const QString& service) {
    qSettings.setValue(CURRENT_SERVICE_KEY, service);
}

bool ApplicationSettings::getShowCloseToSysemTrayMessage() const {
    return qSettings.value(SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY, true).toBool();
}

void ApplicationSettings::setShowCloseToSystemTrayMessage(bool value) {
    qSettings.setValue(SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY, value);
}

QVariant ApplicationSettings::getValue(const QString& key, const QVariant& defaultValue) const {
    return qSettings.value(key, defaultValue);
}

void ApplicationSettings::setValue(const QString& key, const QVariant& value) {
    qSettings.setValue(key, value);
}

QString ApplicationSettings::getTrayIcon() const {
    return qSettings.value(TRAY_ICON_KEY).toString();
}

void ApplicationSettings::setTrayIcon(const QString& trayIcon) {
    qSettings.setValue(TRAY_ICON_KEY, trayIcon);
}

bool ApplicationSettings::getNotificationsEnabled() const {
    return qSettings.value(NOTIFICATIONS_ENABLED_KEY, true).toBool();
}

void ApplicationSettings::setNotificationsEnabled(bool enable) {
    qSettings.setValue(NOTIFICATIONS_ENABLED_KEY, enable);

}

bool ApplicationSettings::isNotificationTypeEnabled(NotificationType notificationType) const {
    if (!getNotificationsEnabled())
        return false;
    return qSettings.value(getNotificationEnabledKey(notificationType), true).toBool();
}

void ApplicationSettings::enableNotificationType(NotificationType notificationType, bool enable) {
    qSettings.setValue(getNotificationEnabledKey(notificationType), enable);
}

QString ApplicationSettings::getNotificationEnabledKey(NotificationType type) const {
    return NOTIFICATION_ENABLED_KEY.arg(static_cast<int>(type));
}
