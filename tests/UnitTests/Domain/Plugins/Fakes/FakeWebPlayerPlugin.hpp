#pragma once

#include <UnitTests/Domain/Plugins/Mocks/MockWebPlayerPlugin.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakeWebPlayerPlugin: public MockWebPlayerPlugin
    {
    public:
        FakeWebPlayerPlugin();
    };
}
