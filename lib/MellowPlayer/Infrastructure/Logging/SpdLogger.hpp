#pragma once

#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <memory>

namespace spdlog
{
    class logger;
}

namespace MellowPlayer::Infrastructure
{
    class SpdLogger : public Domain::ILogger
    {
    public:
        SpdLogger(const std::string& name, const Domain::LoggerConfig& config);
        ~SpdLogger();
        void log(const std::string& message, Domain::LogLevel level, const char* file, int line) override;
        const std::string& name() const override;

    private:
        std::shared_ptr<spdlog::logger> logger_;
        bool includeFileAndLine_;
        std::string name_;
    };
}