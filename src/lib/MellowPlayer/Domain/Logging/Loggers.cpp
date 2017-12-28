#include "Loggers.hpp"
#include "ILogger.hpp"
#include "ILoggerFactory.hpp"
#include <QtCore/QLoggingCategory>

using namespace MellowPlayer::Domain;
using namespace std;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    string category(context.category);
    ILogger& logger = Loggers::logger(category == "default" ? "qt" : category);

    // QtCriticalMsg, QtFatalMsg, QtSystemMsg = QtCriticalMsg
    std::map<int, LogLevel> toLogLevel = {{QtDebugMsg, LogLevel::Debug},
                                          {QtInfoMsg, LogLevel::Info},
                                          {QtWarningMsg, LogLevel::Warning},
                                          {QtCriticalMsg, LogLevel::Error},
                                          {QtFatalMsg, LogLevel::Critical}};
    logger.log(message.toStdString(), toLogLevel[type], context.file, context.line);
}

unique_ptr<Loggers> Loggers::instance_ = nullptr;

Loggers& Loggers::initialize(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig)
{
    instance_.reset(new Loggers(loggerFactory, defaultConfig));
    return *instance_;
}

Loggers& Loggers::initialize(ILoggerFactory& loggerFactory, LogLevel logLevel)
{
    auto& loggingManager = initialize(loggerFactory);
    loggingManager.setDefaultLogLevel(logLevel);
    return loggingManager;
}

Loggers& Loggers::instance()
{
    if (instance_ == nullptr)
        throw logic_error("Loggers::instance called before Loggers::initialize!");
    return *instance_;
}

Loggers::Loggers(ILoggerFactory& loggerFactory, const LoggerConfig& defaultConfig)
        : loggerFactory_(loggerFactory), defaultLoggerConfig_(defaultConfig)
{
    qInstallMessageHandler(messageHandler);
}

ILogger& Loggers::logger()
{
    return logger("root");
}

ILogger& Loggers::logger(const std::string& name)
{
    return logger(name, instance().defaultLoggerConfig_);
}

ILogger& Loggers::logger(const std::string& name, const LoggerConfig& loggerConfig)
{
    if (instance().loggerExists(name))
        return instance().getExistingLogger(name);
    else
        return instance().createNewLogger(name, loggerConfig);
}

bool Loggers::loggerExists(const std::string& name)
{
    return loggersMap_.find(name) != loggersMap_.end();
}

ILogger& Loggers::getExistingLogger(const std::string& name)
{
    return *loggersMap_[name];
}

ILogger& Loggers::createNewLogger(const std::string& name, const LoggerConfig& loggerConfig)
{
    loggersMap_[name] = loggerFactory_.create(name, loggerConfig);
    return getExistingLogger(name);
}

void Loggers::setDefaultLogLevel(LogLevel logLevel)
{
    defaultLoggerConfig_.logLevel = logLevel;

    for(auto logger: loggersMap_) {
        logger->setLogLevel(logLevel);
    }
}
