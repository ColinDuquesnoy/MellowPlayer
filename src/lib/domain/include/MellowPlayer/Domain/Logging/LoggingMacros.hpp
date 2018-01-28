#pragma once

#include "LoggerConfig.hpp"
#include <QString>
#include <sstream>

inline std::ostream& operator<<(std::ostream& os, const QString& string)
{
    os << string.toStdString();
    return os;
}

#define LOG(logger, logEvent, logLevel)                                                                                                              \
    {                                                                                                                                                \
        std::stringstream ss;                                                                                                                        \
        ss << logEvent;                                                                                                                              \
        logger.log(ss.str(), logLevel, __FILE__, __LINE__);                                                                                          \
    }

#define LOG_TRACE(logger, logEvent) LOG(logger, logEvent, LogLevel::Trace)

#define LOG_DEBUG(logger, logEvent) LOG(logger, logEvent, LogLevel::Debug)

#define LOG_INFO(logger, logEvent) LOG(logger, logEvent, LogLevel::Info)

#define LOG_WARN(logger, logEvent) LOG(logger, logEvent, LogLevel::Warning)

#define LOG_ERROR(logger, logEvent) LOG(logger, logEvent, LogLevel::Error)

#define LOG_FATAL(logger, logEvent) LOG(logger, logEvent, LogLevel::Critical)
