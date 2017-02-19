#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/IPlayer.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class PlayerMock{
public:
    static Mock<IPlayer> basicMock();
};
