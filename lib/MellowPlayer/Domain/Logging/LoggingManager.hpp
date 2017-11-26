#pragma once

#include <map>
#include <memory>
#include <string>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>

namespace MellowPlayer::Domain
{
    class ILogger;
    class ILoggerFactory;

    class LoggingManager
    {
    public:
        LoggingManager(const LoggingManager& other) = delete;
        LoggingManager(LoggingManager&&) = default;
        LoggingManager& operator=(const LoggingManager&) = delete;
        LoggingManager& operator=(LoggingManager&&) = default;

        static LoggingManager& initialize(std::unique_ptr<ILoggerFactory>& loggerFactory, const LoggerConfig& defaultConfig = LoggerConfig());
        static LoggingManager& initialize(std::unique_ptr<ILoggerFactory>& loggerFactory, LogLevel logLevel);
        static LoggingManager& instance();

        static ILogger& logger();
        static ILogger& logger(const std::string& name);
        static ILogger& logger(const std::string& name, const LoggerConfig& loggerConfig);

        void setDefaultLogLevel(LogLevel logLevel);

    private:
        LoggingManager(std::unique_ptr<ILoggerFactory>& loggerFactory, const LoggerConfig& defaultConfig);

        bool loggerExists(const std::string& name);
        ILogger& getExistingLogger(const std::string& name);
        ILogger& createNewLogger(const std::string& name, const LoggerConfig& loggerConfig);

        std::unique_ptr<ILoggerFactory> loggerFactory_;
        std::map<std::string, std::unique_ptr<ILogger>> loggersMap_;
        LoggerConfig defaultLoggerConfig_;

        static std::unique_ptr<LoggingManager> instance_;
    };
}
