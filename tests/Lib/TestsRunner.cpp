#include "TestsRunner.hpp"
#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <QtCore/QSettings>
#include <QDebug>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <QtWebEngine/qtwebengineglobal.h>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

int TestsRunner::runTests(int argc, char** argv)
{
    Q_INIT_RESOURCE(infrastructure);
    Q_INIT_RESOURCE(presentation);

    QApplication application(argc, argv);
    application.setApplicationName("MellowPlayer.Tests");
    application.setApplicationDisplayName("MellowPlayer.Tests");
    application.setOrganizationName("MellowPlayer.Tests");
    application.setOrganizationDomain("org.mellowplayer.tests");

    QtWebEngine::initialize();

    SpdLoggerFactory loggerFactory;
    LoggerConfig loggerConfig;
    loggerConfig.createFileLoggers = false;

    try {
        Loggers::instance();
        assert(false);
    }
    catch (const logic_error&) {

    }
    Loggers& loggingManager = Loggers::initialize(loggerFactory, loggerConfig);
    loggingManager.setDefaultLogLevel(LogLevel::Error);

    LOG_DEBUG(loggingManager.logger("tests"), "Starting tests");
    qDebug() << "Starting tests" << BuildConfig::buildInfo();

    QSettings settings;
    settings.clear();
    auto retCode = Catch::Session().run(argc, argv);

    settings.clear();

    return retCode;
}

