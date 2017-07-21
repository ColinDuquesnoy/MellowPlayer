#pragma once

#include <MellowPlayer/Application/Logging/ILoggerFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class SpdLoggerFactory : public Application::ILoggerFactory
    {
    public:
        std::unique_ptr<Application::ILogger> create(const std::string &name,
                                                     const Application::LoggerConfig &loggerConfig) const override;
    };
}
