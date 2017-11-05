#pragma once

#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Domain::Tests
{
    class MockWebPlayerScript: public WebPlayerScript
    {
    public:
        MockWebPlayerScript(const QString& code)
        {
            code_ = code;
        }
        MOCK_METHOD0(load, void());
    };
}
