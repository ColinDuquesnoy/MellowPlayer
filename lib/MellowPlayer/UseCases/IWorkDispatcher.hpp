#pragma once

#include <MellowPlayer/Macros.hpp>
#include <functional>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IWorkDispatcher {
public:
    virtual ~IWorkDispatcher() = default;

    virtual void execute(const std::function<void(void)>& workerFunction) = 0;
};


END_MELLOWPLAYER_NAMESPACE
