#pragma once

#include <MellowPlayer/UseCases/Logging/ILogger.hpp>

namespace spdlog {
class logger;
}

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class SpdLogger: public UseCases::ILogger {
public:
    SpdLogger(const std::string& name, const UseCases::LoggerConfig& config);
    ~SpdLogger();
    void log(const std::string &message, UseCases::LogLevel level, const char* file, int line) override;

private:
    std::shared_ptr<spdlog::logger> logger_;
    bool includeFileAndLine_;
};

END_MELLOWPLAYER_NAMESPACE