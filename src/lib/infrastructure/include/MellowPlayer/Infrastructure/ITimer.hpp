#pragma once

#include <functional>

namespace MellowPlayer::Infrastructure
{
    class ITimer
    {
    public:
        virtual ~ITimer() = default;
        virtual void start(int timeout, std::function<void()> callback) = 0;
        virtual void stop() = 0;
    };
}
