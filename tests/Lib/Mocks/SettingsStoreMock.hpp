#pragma once
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <fakeit.hpp>
#include <memory>

class SettingsStoreMock
{
public:
    static fakeit::Mock<MellowPlayer::Domain::ISettingsStore> get();

    static QString currentService;
    static QMap<QString, QVariant> values;
};
