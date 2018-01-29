#pragma once
#include <MellowPlayer/Domain/Notifications/INotifier.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
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
