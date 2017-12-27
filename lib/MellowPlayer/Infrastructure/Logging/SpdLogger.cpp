#include "SpdLogger.hpp"
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <iostream>

using namespace std;
using namespace spdlog;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

shared_ptr<spdlog::sinks::simple_file_sink_mt> SpdLogger::allSink_ = nullptr;
shared_ptr<spdlog::sinks::rotating_file_sink_mt> SpdLogger::allRotatingSink_ = nullptr;

shared_ptr<logger> SpdLogger::createLogger(const string& name, const LoggerConfig& config)
{
    try {
        // configure sinks
        vector<sink_ptr> sinks;
        if (config.createConsoleLogger) {
#ifdef Q_OS_WIN
            sinks.push_back(make_shared<sinks::stdout_sink_mt>());
#else
            sinks.push_back(make_shared<sinks::ansicolor_sink>(make_shared<sinks::stdout_sink_mt>()));
#endif
        }
        auto logDir = FileHelper::createLogDirectory().toStdString();
        auto logFileName = logDir + name;

        if (SpdLogger::allSink_ == nullptr) {
            SpdLogger::allSink_ = make_shared<sinks::simple_file_sink_mt>(logDir + "All.log", true);
            make_shared<logger>("All", SpdLogger::allSink_)->log(level::info, "*******************************************************************************");
        }

        if (SpdLogger::allRotatingSink_ == nullptr) {
            SpdLogger::allRotatingSink_ = make_shared<sinks::rotating_file_sink_mt>(logDir + "AllRotating", "log", 1024 * 1024 * 20, 5);
            make_shared<logger>("AllRotating", SpdLogger::allRotatingSink_)->log(level::info, "*******************************************************************************");
        }

        sinks.push_back(SpdLogger::allSink_);
        sinks.push_back(SpdLogger::allRotatingSink_);
        auto loggerSpecificSink = make_shared<sinks::rotating_file_sink_mt>(logFileName, "log", 1024 * 1024 * 20, 5);
        make_shared<logger>(name, loggerSpecificSink)->log(level::info, "*******************************************************************************");

        sinks.push_back(loggerSpecificSink);

        // create and register logger
        auto combined_logger = make_shared<logger>(name, begin(sinks), end(sinks));
        combined_logger->set_pattern(config.logFormat);
        combined_logger->set_level(static_cast<level::level_enum>(config.logLevel));
        register_logger(combined_logger);

        return combined_logger;
    }
    // LCOV_EXCL_START
    catch (const spdlog_ex& ex) {
        cout << "SpdLogger (" << name << ") initialization failed: " << ex.what() << endl;
        return nullptr;
    }
    // LCOV_EXCL_STOP
}

SpdLogger::SpdLogger(const string& name, const LoggerConfig& config)
        : logger_(SpdLogger::createLogger(name, config)),
          includeFileAndLine_(config.showFileAndLine),
          name_(name)
{
}

void SpdLogger::log(const string& message, LogLevel level, const char* file, int line)
{
    if (includeFileAndLine_ && file != NULL && level == LogLevel::Trace)
        logger_->log(static_cast<level::level_enum>(level), "{} ( \"{}:{}\" )", message, file, line);
    else
        logger_->log(static_cast<level::level_enum>(level), message.c_str());
}

const string& SpdLogger::name() const
{
    return name_;
}

void SpdLogger::setLogLevel(LogLevel level)
{
    auto spdLogLevel = static_cast<level::level_enum>(level);
    SpdLogger::allRotatingSink_->set_level(spdLogLevel);
    logger_->set_level(spdLogLevel);
}
