#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Presentation/IQtApplication.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

class QtApplicationMock {
public:
    static Mock<IQtApplication> get() {
        Mock<IQtApplication> mock;
        When(Method(mock, run)).AlwaysReturn();
        When(Method(mock, quit)).AlwaysReturn();
        When(Method(mock, requestQuit)).AlwaysReturn();
        return mock;
    }
};
