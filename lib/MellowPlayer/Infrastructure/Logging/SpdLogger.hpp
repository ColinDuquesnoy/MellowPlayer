#pragma once

#include <MellowPlayer/Application/Logging/ILogger.hpp>
#include <memory>

namespace spdlog
{
    class logger;
}

namespace MellowPlayer::Infrastructure
{
    class SpdLogger : public Application::ILogger
    {
    public:
        SpdLogger(const std::string& name, const Application::LoggerConfig& config);
        ~SpdLogger();
        void log(const std::string& message, Application::LogLevel level, const char* file, int line) override;
        const std::string& getName() const override;

    private:
        std::shared_ptr<spdlog::logger> logger;
        bool includeFileAndLine;
        std::string name;
    };
}