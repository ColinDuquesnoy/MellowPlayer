#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IMainWindow {
public:
    virtual ~IMainWindow() = default;

    virtual bool load() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};

END_MELLOWPLAYER_NAMESPACE
