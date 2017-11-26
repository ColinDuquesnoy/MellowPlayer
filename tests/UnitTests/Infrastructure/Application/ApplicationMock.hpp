#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Infrastructure::Tests
{
    class ApplicationMock: public IApplication
    {
    public:
        MOCK_METHOD0(initialize, void());
        MOCK_METHOD0(run, int());
        MOCK_METHOD0(quit, void());
        MOCK_METHOD0(restart, void());
        MOCK_METHOD0(restoreWindow, void());
    };
}
