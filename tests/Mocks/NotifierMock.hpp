#pragma once
#include <MellowPlayer/Application/Notifications/INotifier.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
using namespace fakeit;

class NotifierMock
{
public:
    static Mock<INotifier> get()
    {
        Mock<INotifier> mock;
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, display)).AlwaysReturn(true);
        return mock;
    }
};
