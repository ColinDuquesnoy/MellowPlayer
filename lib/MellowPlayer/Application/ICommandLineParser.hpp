#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Application
{
    enum class LogLevel;

    class ICommandLineParser
    {
    public:
        virtual ~ICommandLineParser() = default;
        virtual QString getService() const = 0;
        virtual int getAutoQuitDelay() const = 0;
        virtual bool isPlayPauseRequested() const = 0;
        virtual bool isNextRequested() const = 0;
        virtual bool isPreviousRequested() const = 0;
        virtual LogLevel getLogLevel() const = 0;
    };
}
