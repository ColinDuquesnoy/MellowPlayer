#pragma once

#include <Common/Macros.hpp>
#include "LoggerConfig.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ILogger {
public:
    ~ILogger() = default;
    virtual void log(const std::string& message, LogLevel level, const char* file, int line) = 0;
};

END_MELLOWPLAYER_NAMESPACE
