#pragma once

#include <memory>
#include <string>
#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>
#include <QMap>

namespace MellowPlayer::Domain
{
    class ILogger;
    class ILoggerFactory;

    class Loggers
    {
    public:
        static Loggers& initialize(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig = LoggerConfig());
        static Loggers& initialize(ILoggerFactory& loggerFactory, LogLevel logLevel);
        static Loggers& instance();

        static ILogger& logger();
        static ILogger& logger(const std::string& name);
        static ILogger& logger(const std::string& name, const LoggerConfig& loggerConfig);

        void setDefaultLogLevel(LogLevel logLevel);

    private:
        Loggers(const Loggers& other) = delete;
        Loggers(Loggers&&) = default;
        Loggers& operator=(const Loggers&) = delete;
        Loggers& operator=(Loggers&&) = default;
        Loggers(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig);

        bool loggerExists(const std::string& name);
        ILogger& getExistingLogger(const std::string& name);
        ILogger& createNewLogger(const std::string& name, const LoggerConfig& loggerConfig);

        ILoggerFactory& loggerFactory_;
        QMap<std::string, std::shared_ptr<ILogger>> loggersMap_;
        LoggerConfig defaultLoggerConfig_;

        static std::unique_ptr<Loggers> instance_;
    };
}
