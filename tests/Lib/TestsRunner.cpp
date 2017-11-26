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
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace std;

int TestsRunner::runTests(int argc, char* argv[])
{
    Q_INIT_RESOURCE(domain);
    Q_INIT_RESOURCE(presentation);

    // The following line causes Google Mock to throw an exception on failure,
    // which will be interpreted by your testing framework as a test failure.
    GTEST_FLAG(throw_on_failure) = true;
    InitGoogleMock(&argc, argv);

    DeprecatedApplicationViewModel webApplication(argc, argv, "MellowPlayer.Tests");

    unique_ptr<ILoggerFactory> loggerFactory = make_unique<SpdLoggerFactory>();
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

