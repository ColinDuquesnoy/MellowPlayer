#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/IMainWindow.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
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
