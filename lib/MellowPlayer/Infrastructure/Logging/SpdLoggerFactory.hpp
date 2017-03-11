#pragma once

#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SpdLoggerFactory: public UseCases::ILoggerFactory {
public:
    std::unique_ptr<UseCases::ILogger> create(
        const std::string &name, const UseCases::LoggerConfig &loggerConfig) const override;
};

END_MELLOWPLAYER_NAMESPACE
