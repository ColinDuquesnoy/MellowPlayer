#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace fakeit;

class SettingsProviderMock {
public:
    static Mock<ISettingsProvider> get();

    static QString currentService;
    static QMap<QString, QVariant> values;
};
