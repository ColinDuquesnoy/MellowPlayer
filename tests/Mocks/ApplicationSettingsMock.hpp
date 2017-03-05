#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/IApplicationSettings.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class ApplicationSettingsMock {
public:
    static Mock<IApplicationSettings> get() {
        Mock<IApplicationSettings> mock;

        When(Method(mock, clear)).AlwaysReturn();

        When(Method(mock, getCurrentService)).AlwaysReturn("Deezer");
        When(Method(mock, setCurrentService)).AlwaysReturn();

        When(Method(mock, showCloseToSysemTrayMessage)).AlwaysReturn(true);
        When(Method(mock, setShowCloseToSystemTrayMessage)).AlwaysReturn();

        When(Method(mock, getValue)).AlwaysReturn(QVariant());
        When(Method(mock, setValue)).AlwaysReturn();

        return mock;
    }
};
