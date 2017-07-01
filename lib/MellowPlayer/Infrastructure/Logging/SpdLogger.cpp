#include <iostream>
#include <spdlog/spdlog.h>
#include <MellowPlayer/Infrastructure/Utils/FileHelper.hpp>
#include "SpdLogger.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;
using namespace spdlog;

shared_ptr<logger> createLogger(const string& name, const LoggerConfig& config) {
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
        auto logFileName = FileHelper::createLogDirectory().toStdString() + name;
        sinks.push_back(make_shared<sinks::rotating_file_sink_mt>(logFileName, "log", 1024 * 1024 * 20, 5));

        // create and register logger
        auto combined_logger = make_shared<logger>(name, begin(sinks), end(sinks));
        combined_logger->set_pattern(config.logFormat);
        combined_logger->set_level(static_cast<level::level_enum>(config.logLevel));
        register_logger(combined_logger);

        return combined_logger;
    }
    // LCOV_EXCL_START
    catch (const spdlog_ex &ex) {
        cout << "SpdLogger (" << name << ") initialization failed: " << ex.what() << endl;
        return nullptr;
    }
    // LCOV_EXCL_STOP
}

SpdLogger::SpdLogger(const string& name, const LoggerConfig& config)
    : logger(createLogger(name, config)), includeFileAndLine(config.showFileAndLine), name(name) {

}

SpdLogger::~SpdLogger() = default;

void SpdLogger::log(const string& message, LogLevel level, const char* file, int line) {
    if (includeFileAndLine && file != NULL && level == LogLevel::Trace)
        logger->log(static_cast<level::level_enum>(level), "{} ( \"{}:{}\" )", message, file, line);
    else
        logger->log(static_cast<level::level_enum>(level), message.c_str());
}

const string& SpdLogger::getName() const {
    return name;
}
