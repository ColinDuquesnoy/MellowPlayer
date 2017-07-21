#pragma once

#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <QCommandLineParser>

namespace MellowPlayer::Infrastructure
{
    class CommandLineParser : public Application::ICommandLineParser
    {
    public:
        CommandLineParser();

        QString getService() const override;
        int getAutoQuitDelay() const override;
        bool isPlayPauseRequested() const override;
        bool isNextRequested() const override;
        bool isPreviousRequested() const override;
        Application::LogLevel getLogLevel() const override;

    private:
        QCommandLineParser parser;
        QCommandLineOption serviceOption;
        QCommandLineOption logLevelOption;
        QCommandLineOption playPauseOption;
        QCommandLineOption nextOption;
        QCommandLineOption previousOption;
        QCommandLineOption autoQuitDelayOption;

        QString service;
        Application::LogLevel logLevel;
        bool playRequested = false;
        bool nextRequested = false;
        bool previousRequested = false;
        int autoQuitDelay = 0;
    };
}
