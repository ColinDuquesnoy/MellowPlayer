#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

class HotkeysControllerMock {
public:
    static Mock<IHotkeysController> get() {
        Mock<IHotkeysController> mock;
        When(Method(mock, start)).AlwaysReturn();
        When(Method(mock, togglePlayPause)).AlwaysReturn();
        When(Method(mock, next)).AlwaysReturn();
        When(Method(mock, previous)).AlwaysReturn();
        When(Method(mock, toggleFavoriteSong)).AlwaysReturn();
        return mock;
    }
};
