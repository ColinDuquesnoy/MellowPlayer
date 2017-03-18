#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class ApplicationSettingsMock {
public:
    static Mock<IApplicationSettings> get() {
        Mock<IApplicationSettings> mock;

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

    static QString currentService;
    static QMap<NotificationType, bool> enabledNotifications;
    static bool notificationsEnabled;
};
