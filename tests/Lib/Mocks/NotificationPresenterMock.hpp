#pragma once
#include <MellowPlayer/Presentation/Notifications/Presenters/INotificationPresenter.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Presentation;
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
