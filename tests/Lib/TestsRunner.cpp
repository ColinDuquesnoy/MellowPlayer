#include "TestsRunner.hpp"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/DeprecatedApplicationViewModel.hpp>
#include <QtCore/QSettings>
#include <QDebug>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace std;

int TestsRunner::runTests(int argc, char* argv[])
{
    Q_INIT_RESOURCE(domain);
    Q_INIT_RESOURCE(presentation);

    DeprecatedApplicationViewModel webApplication(argc, argv, "MellowPlayer.Tests");

    SpdLoggerFactory loggerFactory;
    LoggerConfig loggerConfig;
    loggerConfig.createFileLogger = false;

    try {
        LoggingManager::instance();
        assert(false);
    } catch (const logic_error&) {
    }
    LoggingManager& loggingManager = LoggingManager::initialize(loggerFactory, loggerConfig);
    loggingManager.setDefaultLogLevel(LogLevel::Off);

    LOG_DEBUG(loggingManager.logger("tests"), "Starting tests");
    qDebug() << "Starting tests" << webApplication.buildInfo();

    QSettings settings;
    settings.clear();
    auto retCode = Catch::Session().run(argc, argv);

    settings.clear();
    webApplication.clearCache();
    webApplication.clearCookies();

    return retCode;
}

