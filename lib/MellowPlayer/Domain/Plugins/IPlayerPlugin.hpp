#pragma once

#include "IPlugin.hpp"

namespace MellowPlayer::Domain
{
    class IPlayer;

    class IPlayerPlugin: public IPlugin
    {
        Q_OBJECT
        CONSTANT_OBJECT_PROPERTY(IPlayer, player)
    };
}