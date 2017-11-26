#pragma once

#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <fakeit.hpp>
#include <memory>
#include <gmock/gmock.h>

namespace MellowPlayer::Infrastructure::Tests
{
    class CommandLineArgumentsMock: public ICommandLineArguments
    {
    public:
        MOCK_METHOD0(parse, void());
        MOCK_CONST_METHOD0(service, QString());
        MOCK_CONST_METHOD0(autoQuitDelay, int());
        MOCK_CONST_METHOD0(playPauseRequested, bool());
        MOCK_CONST_METHOD0(nextRequested, bool());
        MOCK_CONST_METHOD0(previousRequested, bool());
        MOCK_CONST_METHOD0(toggleFavoriteRequested, bool());
        MOCK_CONST_METHOD0(logLevel, Domain::LogLevel());
    };
}
