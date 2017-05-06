#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/IApplicationSettings.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class ApplicationSettingsMock {
public:
    static Mock<IApplicationSettings> get();

    static QString currentService;
    static QMap<NotificationType, bool> enabledNotifications;
    static bool notificationsEnabled;
};
