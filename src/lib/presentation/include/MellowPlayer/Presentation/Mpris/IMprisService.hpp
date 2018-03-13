#pragma once

namespace MellowPlayer::Presentation
{
    class IMprisService
    {
    public:
        virtual ~IMprisService() = default;
        virtual bool start() = 0;
    };
}
