#pragma once
#include <MellowPlayer/Domain/Settings/ISettingsProvider.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace fakeit;

class SettingsProviderMock
{
public:
    static Mock<ISettingsProvider> get();

    static QString currentService;
    static QMap<QString, QVariant> values;
};
