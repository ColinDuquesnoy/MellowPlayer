#pragma once

#include <memory>
#include <MellowPlayer/Macros.hpp>
#include "LoggerConfig.hpp"
#include "ILogger.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class ILoggerFactory {
public:
    virtual ~ILoggerFactory() = default;
    virtual std::unique_ptr<ILogger> create(const std::string &name, const LoggerConfig &loggerConfig) const = 0;
};

END_MELLOWPLAYER_NAMESPACE
