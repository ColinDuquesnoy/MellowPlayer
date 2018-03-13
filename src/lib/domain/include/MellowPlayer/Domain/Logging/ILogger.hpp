#pragma once

#include "LoggerConfig.hpp"

namespace MellowPlayer::Domain
{
    class ILogger
    {
    public:
        virtual ~ILogger() = default;
        virtual void log(const std::string& message, LogLevel level, const char* file, int line) = 0;
        virtual const std::string& name() const = 0;
        virtual void setLogLevel(LogLevel level) = 0;
    };
}
