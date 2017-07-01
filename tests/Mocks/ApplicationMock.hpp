#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Infrastructure/Applications/IApplication.hpp>

USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

class ApplicationMock {
public:
    static Mock<IApplication> get() {
        Mock<IApplication> mock;
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, restoreWindow)).AlwaysReturn();
        When(Method(mock, run)).AlwaysReturn();
        When(Method(mock, quit)).AlwaysReturn();
        return mock;
    }
};
