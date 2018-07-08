#pragma once
#include <MellowPlayer/Infrastructure/Hotkeys/IHotkeys.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

class HotkeysControllerMock
{
public:
    static Mock<IHotkeys> get()
    {
        Mock<IHotkeys> mock;
        When(Method(mock, start)).AlwaysReturn();
        When(Method(mock, togglePlayPause)).AlwaysReturn();
        When(Method(mock, next)).AlwaysReturn();
        When(Method(mock, previous)).AlwaysReturn();
        When(Method(mock, toggleFavoriteSong)).AlwaysReturn();
        return mock;
    }
};
