#pragma once

#include <memory>
#include <map>
#include <MellowPlayer/Macros.hpp>
#include "ILoggerFactory.hpp"
#include "LoggingMacros.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class LoggingManager {
public:
    LoggingManager(const LoggingManager& other) = delete;
    LoggingManager(LoggingManager&&) = default;
    LoggingManager& operator=(const LoggingManager&) = delete;
    LoggingManager& operator=(LoggingManager&&) = default;

    static LoggingManager& initialize(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig=LoggerConfig());
    static LoggingManager& initialize(ILoggerFactory& loggerFactory, LogLevel logLevel);
    static LoggingManager& instance();

    ILogger& getLogger();
    ILogger& getLogger(const std::string& name);
    ILogger& getLogger(const std::string& name, const LoggerConfig& loggerConfig);

    void setDefaultLogLevel(LogLevel logLevel);

private:
    LoggingManager(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig);

    bool loggerExists(const std::string& name);
    ILogger& getExistingLogger(const std::string& name);
    ILogger& createNewLogger(const std::string& name, const LoggerConfig& loggerConfig);
    void installQtMessageHandler();

    ILoggerFactory& loggerFactory_;
    std::map<std::string, std::unique_ptr<ILogger>> loggersMap_;
    LoggerConfig defaultLoggerConfig_;

    static std::unique_ptr<LoggingManager> instance_;
};

END_MELLOWPLAYER_NAMESPACE

