#pragma once
#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Logging/LoggerConfig.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
using namespace fakeit;

class CommandLineParserMock
{
public:
    static Mock<ICommandLineParser> get()
    {
        Mock<ICommandLineParser> mock;

        When(Method(mock, service)).AlwaysReturn("");
        When(Method(mock, autoQuitDelay)).AlwaysReturn(0);
        When(Method(mock, playPauseRequested)).AlwaysReturn(false);
        When(Method(mock, nextRequested)).AlwaysReturn(false);
        When(Method(mock, previousRequested)).AlwaysReturn(false);
        When(Method(mock, logLevel)).AlwaysReturn(LogLevel::Info);
        When(Method(mock, toggleFavoriteRequested)).AlwaysReturn(false);

        return mock;
    }
};
