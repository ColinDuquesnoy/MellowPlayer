#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IQtApplication {
public:
    virtual ~IQtApplication() = default;

    virtual int run() = 0;
    virtual void quit() = 0;
};

END_MELLOWPLAYER_NAMESPACE
