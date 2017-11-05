#pragma once

#include <MellowPlayer/Domain/Plugins/WebPlayerPlugin.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Domain::Tests
{
    class MockWebPlayerPlugin: public WebPlayerPlugin
    {
    public:
        MOCK_METHOD0(load, void());
    };
}
