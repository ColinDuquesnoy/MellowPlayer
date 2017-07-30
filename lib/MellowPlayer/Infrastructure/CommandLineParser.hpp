#pragma once

#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Logging/LoggerConfig.hpp>
#include <QCommandLineParser>

namespace MellowPlayer::Infrastructure
{
    class CommandLineParser : public Application::ICommandLineParser
    {
    public:
        CommandLineParser();

        QString service() const override;
        int autoQuitDelay() const override;
        bool playPauseRequested() const override;
        bool nextRequested() const override;
        bool previousRequested() const override;
        bool toggleFavoriteRequested() const override;
        Application::LogLevel logLevel() const override;

    private:
        QCommandLineParser parser_;
        QCommandLineOption serviceOption_;
        QCommandLineOption logLevelOption_;
        QCommandLineOption playPauseOption_;
        QCommandLineOption nextOption_;
        QCommandLineOption previousOption_;
        QCommandLineOption toggleFavoriteOption_;
        QCommandLineOption autoQuitDelayOption_;

        QString service_;
        Application::LogLevel logLevel_;
        bool playRequested_ = false;
        bool nextRequested_ = false;
        bool previousRequested_ = false;
        bool toggleFavoriteRequested_ = false;
        int autoQuitDelay_ = 0;
    };
}
