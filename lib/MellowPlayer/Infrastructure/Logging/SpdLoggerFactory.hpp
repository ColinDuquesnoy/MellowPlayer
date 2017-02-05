#pragma once

#include <MellowPlayer/Logging/ILoggerFactory.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SpdLoggerFactory: public Logging::ILoggerFactory {
public:
    std::unique_ptr<Logging::ILogger> create(
        const std::string &name, const Logging::LoggerConfig &loggerConfig) const override;
};

END_MELLOWPLAYER_NAMESPACE
