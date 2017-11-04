#pragma once

namespace MellowPlayer::Domain
{
    class IMprisController
    {
    public:
        virtual ~IMprisController() = default;
        virtual bool start() = 0;
    };
}