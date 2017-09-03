#include "TestsRunner.hpp"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <QtCore/QSettings>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace std;

int TestsRunner::runTests(int argc, char* argv[])
{
    Q_INIT_RESOURCE(application);
    Q_INIT_RESOURCE(presentation);

    ApplicationViewModel webApplication(argc, argv, "MellowPlayer3.Tests");

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
    auto retCode = Catch::Session().run(argc, const_cast<char const* const* const>(argv));

    settings.clear();
    webApplication.clearCache();
    webApplication.clearCookies();

    return retCode;
}

