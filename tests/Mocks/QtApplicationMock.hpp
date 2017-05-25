#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/IQtApplication.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
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
