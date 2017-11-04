#pragma once
#include <MellowPlayer/Domain/IQtApplication.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
using namespace fakeit;

class QtApplicationMock
{
public:
    static Mock<IQtApplication> get()
    {
        Mock<IQtApplication> mock;
        When(Method(mock, run)).AlwaysReturn();
        When(Method(mock, quit)).AlwaysReturn();
        When(Method(mock, requestQuit)).AlwaysReturn();
        return mock;
    }
};
