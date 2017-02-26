#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class IApplication
{
public:
    virtual void initialize() = 0;
    virtual int run() = 0;
    virtual void restoreWindow() = 0;
    virtual void quit() = 0;
};


END_MELLOWPLAYER_NAMESPACE