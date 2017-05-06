#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/ISystemTrayIcon.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class SystemTrayIconMock {
public:
    static Mock<ISystemTrayIcon> get() {
        Mock<ISystemTrayIcon> mock;

        When(Method(mock, show)).AlwaysReturn();
        When(Method(mock, hide)).AlwaysReturn();
        When(Method(mock, showMessage)).AlwaysReturn();

        return mock;
    }
};
