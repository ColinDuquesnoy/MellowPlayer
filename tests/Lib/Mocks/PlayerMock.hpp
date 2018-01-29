#pragma once
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
using namespace fakeit;

class PlayerMock
{
public:
    static Mock<IPlayer> get()
    {
        Mock<IPlayer> mock;
        When(Method(mock, togglePlayPause)).AlwaysReturn();
        When(Method(mock, next)).AlwaysReturn();
        When(Method(mock, previous)).AlwaysReturn();
        When(Method(mock, toggleFavoriteSong)).AlwaysReturn();

        return mock;
    }
};
