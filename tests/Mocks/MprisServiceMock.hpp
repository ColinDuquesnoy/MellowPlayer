#pragma once

#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Infrastructure/Services/IMprisService.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

class MprisServiceMock {
public:
    static Mock<IMprisService> get() {
        Mock<IMprisService> mock;
        When(Method(mock, start)).AlwaysReturn();
        return mock;
    }
};
