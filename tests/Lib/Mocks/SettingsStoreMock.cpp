#include "SettingsStoreMock.hpp"
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <QMap>
#include <QString>
#include <QVariant>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace fakeit;


QMap<QString, QVariant> SettingsStoreMock::values;

Mock<ISettingsStore> SettingsStoreMock::get()
{
    Mock<ISettingsStore> mock;

    When(Method(mock, clear)).AlwaysDo([]() { values.clear(); });

    When(Method(mock, value)).AlwaysDo([](const QString& key, const QVariant& defaultValue) -> QVariant {
        if (values.contains(key))
            return values[key];
        return defaultValue;
    });
    When(Method(mock, setValue)).AlwaysDo([](const QString& key, const QVariant& value) { values[key] = value; });

    values.clear();

    return mock;
}
