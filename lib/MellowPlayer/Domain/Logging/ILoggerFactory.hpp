#pragma once

#include <memory>
#include <string>

namespace MellowPlayer::Domain
{
    class ILogger;
    struct LoggerConfig;

    class ILoggerFactory
    {
    public:
        virtual ~ILoggerFactory() = default;
        virtual std::unique_ptr<ILogger> create(const std::string& name, const LoggerConfig& loggerConfig) const = 0;
    };
}
