#pragma once
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
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
