#pragma once

#include <MellowPlayer/Domain/IWorkDispatcher.hpp>

class FakeWorkDispatcher : public MellowPlayer::Domain::IWorkDispatcher
{
public:
    void invoke(const std::function<void(void)>& workerFunction) override
    {
        workerFunction();
    };

    void delayInvoke(int, const std::function<void(void)>& workerFunction) override
    {
        workerFunction();
    }
};
