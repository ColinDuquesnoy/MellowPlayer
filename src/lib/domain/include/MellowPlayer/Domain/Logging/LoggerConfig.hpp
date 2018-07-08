#pragma once

#include <string>

namespace MellowPlayer::Domain
{
    /**
     * @brief Enumerates the possible log levels.
     */
    enum class LogLevel
    {
        Trace = 0,
        Debug = 1,
        Info = 2,
        Warning = 3,
        Error = 4,
        Critical = 5,
        Off = 6,
    };

    /**
     * @brief Stores the configuration of a logger.
     */
    struct LoggerConfig
    {
        /**
         * @brief Global log level.
         *
         * Default is LogLevel::Info.
         */
        LogLevel logLevel;

        /**
         * @brief Log format, see
         * https://github.com/gabime/spdlog/wiki/3.-Custom-formatting.
         *
         * Default is "%l [%H:%M:%S] - %n: "%v"".
         */
        std::string logFormat;

        /**
         * @brief True to create console logger. Default is true.
         */
        bool createConsoleLogger;

        /**
         * @brief True to create a file loggers. Default is true.
         */
        bool createFileLoggers;

        /**
         * @brief True to show file and line where log record was emitted. Default is
         * true.
         */
        bool showFileAndLine;

        LoggerConfig();

        static std::string DEFAULT_LOG_FORMAT;
    };
}