#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Notifications/INotifier.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

class NotifierMock {
public:
    static Mock<INotifier> get() {
        Mock<INotifier> mock;
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, display)).AlwaysReturn(true);
        return mock;
    }
};

