#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Domain
{
    enum class LogLevel;

    class ICommandLineParser
    {
    public:
        virtual ~ICommandLineParser() = default;
        virtual QString service() const = 0;
        virtual int autoQuitDelay() const = 0;
        virtual bool playPauseRequested() const = 0;
        virtual bool nextRequested() const = 0;
        virtual bool previousRequested() const = 0;
        virtual bool toggleFavoriteRequested() const = 0;
        virtual LogLevel logLevel() const = 0;
    };
}
