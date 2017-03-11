#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

class HotkeysServiceMock {
public:
    static Mock<IHotkeysService> get() {
        Mock<IHotkeysService> mock;
        When(Method(mock, togglePlayPause)).AlwaysReturn();
        When(Method(mock, next)).AlwaysReturn();
        When(Method(mock, previous)).AlwaysReturn();
        When(Method(mock, toggleFavoriteSong)).AlwaysReturn();
        return mock;
    }
};
