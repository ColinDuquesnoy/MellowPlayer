#pragma once

#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Domain::Tests
{
    class MockWebPlayerScript: public WebPlayerScript
    {
    public:
        MOCK_METHOD0(load, void());
    };
}
