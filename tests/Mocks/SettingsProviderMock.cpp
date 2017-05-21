#include "SettingsProviderMock.hpp"

QString SettingsProviderMock::currentService;
QMap<QString, QVariant> SettingsProviderMock::values;

Mock<ISettingsProvider> SettingsProviderMock::get() {
    Mock<ISettingsProvider> mock;

    When(Method(mock, clear)).AlwaysReturn();

    When(Method(mock, getCurrentService)).AlwaysReturn(currentService);
    When(Method(mock, setCurrentService)).AlwaysDo([](const QString& serviceName) {
        currentService = serviceName;
    });

    When(Method(mock, getShowCloseToSysemTrayMessage)).AlwaysReturn(true);
    When(Method(mock, setShowCloseToSystemTrayMessage)).AlwaysReturn();

    When(Method(mock, getValue)).AlwaysDo([](const QString& key, const QVariant& defaultValue) -> QVariant {
        if (values.contains(key))
            return values[key];
        return defaultValue;
    });
    When(Method(mock, setValue)).AlwaysDo([](const QString& key, const QVariant& value){
        values[key] = value;
    });

    return mock;
}
