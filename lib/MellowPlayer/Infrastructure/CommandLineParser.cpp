#include "CommandLineParser.hpp"
#include <QDebug>
#include <MellowPlayer/Application/Logging/LoggerConfig.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

CommandLineParser::CommandLineParser()
        : serviceOption_(QStringList() << "s"
                                       << "service",
                         "Select startup service", "service"),
          logLevelOption_(QStringList() << "l"
                                        << "log-level",
                          "Log level (0=TRACE, 1=DEBUG, 2=INFO, 3=WARNING, 4=ERROR, 5=CRITICAL, 6=OFF)", "logLevel", "2"),
          playPauseOption_(QStringList() << "p"
                                         << "play-pause",
                           "Play or pause the current song"),
          nextOption_(QStringList() << "f"
                                    << "next",
                      "Skip to the next song"),
          previousOption_(QStringList() << "b"
                                        << "previous",
                          "Skip to the previous song"),
          toggleFavoriteOption_(QStringList() << "t"
                                              << "toggle-favorite-song",
                                "Add or remove the current song to/from your favorites"),
          autoQuitDelayOption_(QStringList() << "d"
                                             << "auto-quit-delay",
                               "Auto quit delay [ms]", "autoQuitDelay")
{
    parser_.setApplicationDescription("Cloud music player for your desktop!");
    parser_.addVersionOption();
    parser_.addHelpOption();
    parser_.addOption(serviceOption_);
    parser_.addOption(logLevelOption_);
    parser_.addOption(playPauseOption_);
    parser_.addOption(nextOption_);
    parser_.addOption(previousOption_);
    parser_.addOption(toggleFavoriteOption_);
    parser_.addOption(autoQuitDelayOption_);

    QStringList webEngineOptions = QStringList() << "--remote-debugging-port";
    QStringList args;
    for (auto arg : qApp->arguments()) {
        bool addArg = true;
        for (auto webEngineOption : webEngineOptions) {
            if (arg.startsWith(webEngineOption)) {
                addArg = false;
                break;
            }
        }
        if (addArg)
            args << arg;
    }
    parser_.process(args);

    service_ = parser_.value(serviceOption_);
    int logLevelValue = parser_.value(logLevelOption_).toInt();
    if (logLevelValue < 0 || logLevelValue > static_cast<int>(LogLevel::Off))
        logLevel_ = LogLevel::Info;
    else
        logLevel_ = static_cast<LogLevel>(logLevelValue);
    autoQuitDelay_ = parser_.value(autoQuitDelayOption_).toInt();

    playRequested_ = parser_.isSet(playPauseOption_);
    previousRequested_ = parser_.isSet(previousOption_);
    nextRequested_ = parser_.isSet(nextOption_);
    toggleFavoriteRequested_ = parser_.isSet(toggleFavoriteOption_);
}

QString CommandLineParser::service() const
{
    return service_;
}

int CommandLineParser::autoQuitDelay() const
{
    return autoQuitDelay_;
}

bool CommandLineParser::playPauseRequested() const
{
    return playRequested_;
}

bool CommandLineParser::nextRequested() const
{
    return nextRequested_;
}

bool CommandLineParser::previousRequested() const
{
    return previousRequested_;
}

LogLevel CommandLineParser::logLevel() const
{
    return logLevel_;
}
bool CommandLineParser::toggleFavoriteRequested() const
{
    return toggleFavoriteRequested_;
}
