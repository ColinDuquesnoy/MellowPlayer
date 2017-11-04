#pragma once

#include <MellowPlayer/Domain/Logging/ILoggerFactory.hpp>

namespace MellowPlayer::Domain
{
    class ILogger;
    struct LoggerConfig;
}

namespace MellowPlayer::Infrastructure
{
    class SpdLoggerFactory : public Domain::ILoggerFactory
    {
    public:
        std::unique_ptr<Domain::ILogger> create(const std::string& name, const Domain::LoggerConfig& loggerConfig) const override;
    };
}
