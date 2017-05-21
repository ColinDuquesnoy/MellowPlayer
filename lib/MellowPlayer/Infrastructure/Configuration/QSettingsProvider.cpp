#include "QSettingsProvider.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

const QString QSettingsProvider::CURRENT_SERVICE_KEY = "currentService";
const QString QSettingsProvider::SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY = "showCloseToSystemTrayMessage";
const QString QSettingsProvider::TRAY_ICON_KEY = "getTrayIcon";
const QString QSettingsProvider::NOTIFICATIONS_ENABLED_KEY = "notificationsEnabled";
const QString QSettingsProvider::NOTIFICATION_ENABLED_KEY = "notification/%1";

QSettingsProvider::QSettingsProvider(): qSettings() {

}

void QSettingsProvider::clear() {
    qSettings.clear();
}

QString QSettingsProvider::getCurrentService() const {
    return qSettings.value(CURRENT_SERVICE_KEY, "").toString();
}

void QSettingsProvider::setCurrentService(const QString& service) {
    qSettings.setValue(CURRENT_SERVICE_KEY, service);
}

bool QSettingsProvider::getShowCloseToSysemTrayMessage() const {
    return qSettings.value(SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY, true).toBool();
}

void QSettingsProvider::setShowCloseToSystemTrayMessage(bool value) {
    qSettings.setValue(SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY, value);
}

QVariant QSettingsProvider::getValue(const QString& key, const QVariant& defaultValue) const {
    return qSettings.value(key, defaultValue);
}

void QSettingsProvider::setValue(const QString& key, const QVariant& value) {
    qSettings.setValue(key, value);
}

QString QSettingsProvider::getTrayIcon() const {
    return qSettings.value(TRAY_ICON_KEY).toString();
}

void QSettingsProvider::setTrayIcon(const QString& trayIcon) {
    qSettings.setValue(TRAY_ICON_KEY, trayIcon);
}

bool QSettingsProvider::getNotificationsEnabled() const {
    return qSettings.value(NOTIFICATIONS_ENABLED_KEY, true).toBool();
}

void QSettingsProvider::setNotificationsEnabled(bool enable) {
    qSettings.setValue(NOTIFICATIONS_ENABLED_KEY, enable);

}

bool QSettingsProvider::isNotificationTypeEnabled(NotificationType notificationType) const {
    if (!getNotificationsEnabled())
        return false;
    return qSettings.value(getNotificationEnabledKey(notificationType), true).toBool();
}

void QSettingsProvider::enableNotificationType(NotificationType notificationType, bool enable) {
    qSettings.setValue(getNotificationEnabledKey(notificationType), enable);
}

QString QSettingsProvider::getNotificationEnabledKey(NotificationType type) const {
    return NOTIFICATION_ENABLED_KEY.arg(static_cast<int>(type));
}
