#include "LoggingManager.hpp"
#include "ILogger.hpp"
#include "ILoggerFactory.hpp"
#include <QtCore/QLoggingCategory>

using namespace MellowPlayer::Domain;
using namespace std;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    string category(context.category);
    ILogger& logger = LoggingManager::logger(category == "default" ? "qt" : category);

    // QtCriticalMsg, QtFatalMsg, QtSystemMsg = QtCriticalMsg
    std::map<int, LogLevel> toLogLevel = {{QtDebugMsg, LogLevel::Debug},
                                          {QtInfoMsg, LogLevel::Info},
                                          {QtWarningMsg, LogLevel::Warning},
                                          {QtCriticalMsg, LogLevel::Error},
                                          {QtFatalMsg, LogLevel::Critical}};
    logger.log(message.toStdString(), toLogLevel[type], context.file, context.line);
}

unique_ptr<LoggingManager> LoggingManager::instance_ = nullptr;

LoggingManager& LoggingManager::initialize(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig)
{
    instance_.reset(new LoggingManager(loggerFactory, defaultConfig));
    return *instance_;
}

LoggingManager& LoggingManager::initialize(ILoggerFactory& loggerFactory, LogLevel logLevel)
{
    auto& loggingManager = initialize(loggerFactory);
    loggingManager.setDefaultLogLevel(logLevel);
    return loggingManager;
}

LoggingManager& LoggingManager::instance()
{
    if (instance_ == nullptr)
        throw logic_error("LoggingManager::instance called before LoggingManager::initialize!");
    return *instance_;
}

LoggingManager::LoggingManager(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig)
        : loggerFactory_(loggerFactory), defaultLoggerConfig_(defaultConfig)
{
    qInstallMessageHandler(messageHandler);
}

ILogger& LoggingManager::logger()
{
    return logger("root");
}

ILogger& LoggingManager::logger(const std::string& name)
{
    return logger(name, instance().defaultLoggerConfig_);
}

ILogger& LoggingManager::logger(const std::string& name, const LoggerConfig& loggerConfig)
{
    if (instance().loggerExists(name))
        return instance().getExistingLogger(name);
    else
        return instance().createNewLogger(name, loggerConfig);
}

bool LoggingManager::loggerExists(const std::string& name)
{
    return loggersMap_.find(name) != loggersMap_.end();
}

ILogger& LoggingManager::getExistingLogger(const std::string& name)
{
    return *loggersMap_[name];
}

ILogger& LoggingManager::createNewLogger(const std::string& name, const LoggerConfig& loggerConfig)
{
    loggersMap_[name] = loggerFactory_.create(name, loggerConfig);
    return getExistingLogger(name);
}

void LoggingManager::setDefaultLogLevel(LogLevel logLevel)
{
    defaultLoggerConfig_.logLevel = logLevel;
}
