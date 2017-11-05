#pragma once

namespace MellowPlayer::Infrastructure
{
    class IMpris
    {
    public:
        virtual ~IMpris() = default;
        virtual bool start() = 0;
    };
}