#pragma once
#include <MellowPlayer/Presentation/Notifications/ISystemTrayIcon.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Presentation;
using namespace fakeit;

class SystemTrayIconMock
{
public:
    static Mock<ISystemTrayIcon> get()
    {
        Mock<ISystemTrayIcon> mock;

        When(Method(mock, show)).AlwaysReturn();
        When(Method(mock, hide)).AlwaysReturn();
        When(Method(mock, showMessage)).AlwaysReturn();

        return mock;
    }
};
