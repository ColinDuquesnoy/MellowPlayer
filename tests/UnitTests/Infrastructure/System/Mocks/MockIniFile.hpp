#pragma once

#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>
#include <gmock/gmock.h>


namespace MellowPlayer::Infrastructure::Tests
{
    class MockIniFile: public IIniFile
    {
    public:
        MOCK_CONST_METHOD1(value, QVariant(const QString&));
        MOCK_CONST_METHOD2(value, QVariant(const QString&, const QVariant&));
    };
}

