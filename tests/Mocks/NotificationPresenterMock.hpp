#pragma once
#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
using namespace fakeit;

class NotificationPresenterMock
{
public:
    static Mock<INotificationPresenter> get()
    {
        Mock<INotificationPresenter> mock;
        Reset(mock);
        return mock;
    }

    static void Reset(Mock<INotificationPresenter>& mock)
    {
        mock.Reset();
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, display)).AlwaysReturn(true);
    }
};
