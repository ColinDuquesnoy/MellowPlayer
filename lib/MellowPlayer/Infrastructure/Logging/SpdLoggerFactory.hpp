#pragma once

#include <MellowPlayer/Application/Logging/ILoggerFactory.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SpdLoggerFactory: public Application::ILoggerFactory {
public:
    std::unique_ptr<Application::ILogger> create(
        const std::string &name, const Application::LoggerConfig &loggerConfig) const override;
};

END_MELLOWPLAYER_NAMESPACE
