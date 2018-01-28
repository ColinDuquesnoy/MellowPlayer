#include <MellowPlayer/Domain/Logging/LoggerConfig.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

string LoggerConfig::DEFAULT_LOG_FORMAT = "[%L] [%Y-%m-%d %H-%M-%S:%f] [%n] %v";

LoggerConfig::LoggerConfig()
{
    logLevel = LogLevel::Debug;
    logFormat = DEFAULT_LOG_FORMAT;
    createConsoleLogger = true;
    createFileLoggers = true;
    showFileAndLine = true;
}
