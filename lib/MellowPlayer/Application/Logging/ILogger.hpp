#pragma once

#include "LoggerConfig.hpp"

namespace MellowPlayer::Application {

    class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual void log(const std::string& message, LogLevel level, const char* file, int line) = 0;
        virtual const std::string& getName() const = 0;
    };

}
