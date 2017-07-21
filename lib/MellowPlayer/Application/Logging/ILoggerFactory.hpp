#pragma once

#include "ILogger.hpp"
#include "LoggerConfig.hpp"
#include <memory>

namespace MellowPlayer::Application
{
    class ILoggerFactory
    {
    public:
        virtual ~ILoggerFactory() = default;
        virtual std::unique_ptr<ILogger> create(const std::string &name, const LoggerConfig &loggerConfig) const = 0;
    };
}
