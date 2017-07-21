#pragma once

namespace MellowPlayer::Application
{
    class IMprisController
    {
    public:
        virtual ~IMprisController() = default;
        virtual bool start() = 0;
    };
}