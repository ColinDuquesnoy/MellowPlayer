#include "SettingsProviderMock.hpp"

QString SettingsProviderMock::currentService;
QMap<NotificationType, bool> SettingsProviderMock::enabledNotifications;
bool SettingsProviderMock::notificationsEnabled = true;

Mock<ISettingsProvider> SettingsProviderMock::get() {
    Mock<ISettingsProvider> mock;

    When(Method(mock, clear)).AlwaysReturn();

    When(Method(mock, getCurrentService)).AlwaysReturn(currentService);
    When(Method(mock, setCurrentService)).AlwaysDo([](const QString& serviceName) {
        currentService = serviceName;
    });

    When(Method(mock, getShowCloseToSysemTrayMessage)).AlwaysReturn(true);
    When(Method(mock, setShowCloseToSystemTrayMessage)).AlwaysReturn();

    When(Method(mock, getTrayIcon)).AlwaysReturn("");
    When(Method(mock, setTrayIcon)).AlwaysReturn();

    When(Method(mock, getValue)).AlwaysReturn(QVariant());
    When(Method(mock, setValue)).AlwaysReturn();

    When(Method(mock, getNotificationsEnabled)).AlwaysDo([]() -> bool {
        return notificationsEnabled;
    });
    When(Method(mock, setNotificationsEnabled)).AlwaysDo([](bool enable) {
        notificationsEnabled = enable;
    });

    When(Method(mock, isNotificationTypeEnabled)).AlwaysDo([](NotificationType type) -> bool {
        if (enabledNotifications.contains(type))
            return enabledNotifications[type];
        return true;
    });
    When(Method(mock, enableNotificationType)).AlwaysDo([](NotificationType type, bool enable) {
        enabledNotifications[type] = enable;
    });

    return mock;
}
