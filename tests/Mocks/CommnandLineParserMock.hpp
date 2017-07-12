#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Logging/LoggerConfig.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

class CommandLineParserMock {
public:
    static Mock<ICommandLineParser> get() {
        Mock<ICommandLineParser> mock;
        When(Method(mock, getService)).AlwaysReturn("");
        When(Method(mock, getAutoQuitDelay)).AlwaysReturn(0);
        When(Method(mock, isPlayPauseRequested)).AlwaysReturn(false);
        When(Method(mock, isNextRequested)).AlwaysReturn(false);
        When(Method(mock, isPreviousRequested)).AlwaysReturn(false);
        When(Method(mock, getLogLevel)).AlwaysReturn(LogLevel::Info);

        return mock;
    }
};

