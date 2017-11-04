#pragma once
#include <MellowPlayer/Domain/IMainWindow.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
using namespace fakeit;

class MainWindowMock
{
public:
    static Mock<IMainWindow> get()
    {
        Mock<IMainWindow> mock;
        When(Method(mock, load)).AlwaysReturn();
        When(Method(mock, show)).AlwaysReturn();
        When(Method(mock, hide)).AlwaysReturn();
        return mock;
    }
};
