#include "LoggerConfig.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

string LoggerConfig::DEFAULT_LOG_FORMAT = "[%L] [%Y-%m-%d %H-%M-%S:%f] [%n] %v";

LoggerConfig::LoggerConfig() {
    logLevel = LogLevel::Info;
    logFormat = DEFAULT_LOG_FORMAT;
    createConsoleLogger = true;
    createFileLogger = true;
    showFileAndLine = true;
}
