#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Player/IPlayer.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace fakeit;

class PlayerMock{
public:
    static Mock<IPlayer> get() {
        Mock<IPlayer> mock;
        When(Method(mock, togglePlayPause)).AlwaysReturn();
        When(Method(mock, next)).AlwaysReturn();
        When(Method(mock, previous)).AlwaysReturn();
        When(Method(mock, toggleFavoriteSong)).AlwaysReturn();

        return mock;
    }
};
