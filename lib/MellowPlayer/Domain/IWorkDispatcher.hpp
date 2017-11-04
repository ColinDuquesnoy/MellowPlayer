#pragma once

#include <functional>

namespace MellowPlayer::Domain
{
    class IWorkDispatcher
    {
    public:
        virtual ~IWorkDispatcher() = default;

        virtual void invoke(const std::function<void(void)>& workerFunction) = 0;
        virtual void delayInvoke(int delayMilliseconds, const std::function<void(void)>& workerFunction) = 0;
    };
}
