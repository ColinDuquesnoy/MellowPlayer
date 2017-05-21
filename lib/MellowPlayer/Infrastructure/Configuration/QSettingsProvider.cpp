#include "QSettingsProvider.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

const QString QSettingsProvider::CURRENT_SERVICE_KEY = "currentService";
const QString QSettingsProvider::SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY = "showCloseToSystemTrayMessage";
const QString QSettingsProvider::TRAY_ICON_KEY = "getTrayIcon";

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
