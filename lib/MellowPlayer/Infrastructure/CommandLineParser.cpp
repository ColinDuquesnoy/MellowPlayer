#include <MellowPlayer/Application/Logging/LoggerConfig.hpp>
#include "CommandLineParser.hpp"
#include <QDebug>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

CommandLineParser::CommandLineParser():
        serviceOption(QStringList() << "s" << "service", "Select startup service", "service"),
        logLevelOption(QStringList() << "l" << "log-level", "Log level (0=TRACE, 1=DEBUG, 2=INFO, 3=WARNING, 4=ERROR, 5=CRITICAL, 6=OFF", "logLevel", "2"),
        playPauseOption(QStringList() << "p" << "play-pause", "Play or pause the current song"),
        nextOption(QStringList() << "f" << "next", "Skip to the next song"),
        previousOption(QStringList() << "b" << "previous", "Skip to the previous song"),
        autoQuitDelayOption(QStringList() << "d" << "auto-quit-delay", "Auto quit delay [ms]", "autoQuitDelay") {
    parser.setApplicationDescription("Cloud music player for your desktop!");
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(serviceOption);
    parser.addOption(logLevelOption);
    parser.addOption(playPauseOption);
    parser.addOption(nextOption);
    parser.addOption(previousOption);
    parser.addOption(autoQuitDelayOption);

    QStringList webEngineOptions = QStringList() << "--remote-debugging-port";
    QStringList args;
    for (auto arg: qApp->arguments()) {
        bool addArg = true;
        for(auto webEngineOption: webEngineOptions) {
            if (arg.startsWith(webEngineOption)) {
                addArg = false;
                break;
            }
        }
        if (addArg)
            args << arg;
    }
    parser.process(args);

    service = parser.value(serviceOption);
    int logLevelValue = parser.value(logLevelOption).toInt();
    if (logLevelValue < 0 || logLevelValue > static_cast<int>(LogLevel::Off))
        logLevel = LogLevel::Info;
    logLevel = static_cast<LogLevel>(logLevelValue);
    autoQuitDelay = parser.value(autoQuitDelayOption).toInt();

    playRequested = parser.isSet(playPauseOption);
    previousRequested = parser.isSet(previousOption);
    nextRequested = parser.isSet(nextOption);
}

QString CommandLineParser::getService() const {
    return service;
}

int CommandLineParser::getAutoQuitDelay() const {
    return autoQuitDelay;
}

bool CommandLineParser::isPlayPauseRequested() const {
    return playRequested;
}

bool CommandLineParser::isNextRequested() const {
    return nextRequested;
}

bool CommandLineParser::isPreviousRequested() const {
    return previousRequested;
}

LogLevel CommandLineParser::getLogLevel() const {
    return logLevel;
}
