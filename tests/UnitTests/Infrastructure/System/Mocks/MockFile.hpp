#pragma once

#include <MellowPlayer/Infrastructure/System/IFile.hpp>
#include <gmock/gmock.h>

namespace MellowPlayer::Infrastructure::Tests
{
    class MockFile: public IFile
    {
    public:
        MOCK_METHOD0(openReadOnly, bool());
        MOCK_METHOD0(readAll, QString());
        MOCK_CONST_METHOD0(exists, bool());
    };
}