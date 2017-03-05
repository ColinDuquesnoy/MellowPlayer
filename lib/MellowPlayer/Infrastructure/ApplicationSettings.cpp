#include "ApplicationSettings.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

const QString ApplicationSettings::CURRENT_SERVICE_KEY = "currentService";
const QString ApplicationSettings::SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY = "showCloseToSystemTrayMessage";
const QString ApplicationSettings::TRAY_ICON_KEY = "getTrayIcon";

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

