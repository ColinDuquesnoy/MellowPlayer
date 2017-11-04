#pragma once

#include <MellowPlayer/Domain/ICommandLineParser.hpp>
#include <QCommandLineParser>

namespace MellowPlayer::Domain
{
    enum class LogLevel;    
}

namespace MellowPlayer::Infrastructure
{
    class CommandLineParser : public Domain::ICommandLineParser
    {
    public:
        CommandLineParser();

        QString service() const override;
        int autoQuitDelay() const override;
        bool playPauseRequested() const override;
        bool nextRequested() const override;
        bool previousRequested() const override;
        bool toggleFavoriteRequested() const override;
        Domain::LogLevel logLevel() const override;

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
        Domain::LogLevel logLevel_;
        bool playRequested_ = false;
        bool nextRequested_ = false;
        bool previousRequested_ = false;
        bool toggleFavoriteRequested_ = false;
        int autoQuitDelay_ = 0;
    };
}
