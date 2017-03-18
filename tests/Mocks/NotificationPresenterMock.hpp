#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class NotificationPresenterMock {
public:
    static Mock<INotificationPresenter> get() {
        Mock<INotificationPresenter> mock;
        Reset(mock);
        return mock;
    }

    static void Reset(Mock<INotificationPresenter>& mock) {
        mock.Reset();
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, display)).AlwaysReturn(true);
    }
};

