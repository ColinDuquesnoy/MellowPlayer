#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace fakeit;

class SettingsProviderMock {
public:
    static Mock<ISettingsProvider> get();

    static QString currentService;
    static QMap<QString, QVariant> values;
};
