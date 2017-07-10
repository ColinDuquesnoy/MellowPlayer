#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

class MainWindowMock {
public:
    static Mock<IMainWindow> get() {
        Mock<IMainWindow> mock;
        When(Method(mock, load)).AlwaysReturn();
        When(Method(mock, show)).AlwaysReturn();
        When(Method(mock, hide)).AlwaysReturn();
        return mock;
    }
};
