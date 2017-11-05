#pragma once

#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakeWebPlayerPlugin: public WebPlayerPlugin
    {
    public:
        void load() override;
    };
}
