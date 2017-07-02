#pragma once

#include <MellowPlayer/Macros.hpp>
#include <functional>

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class IWorkDispatcher {
public:
    virtual ~IWorkDispatcher() = default;

    virtual void invoke(const std::function<void(void)>& workerFunction) = 0;
    virtual void delayInvoke(int delayMilliseconds, const std::function<void(void)>& workerFunction) = 0;
};

END_MELLOWPLAYER_NAMESPACE
