#define CATCH_CONFIG_RUNNER
#include <stdexcept>
#include "catch.hpp"
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
USING_MELLOWPLAYER_NAMESPACE(Presentation)
using namespace std;

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(use_cases);
    Q_INIT_RESOURCE(presentation);

    ApplicationViewModel webApplication(argc, argv, "MellowPlayer3.Tests");

    SpdLoggerFactory loggerFactory;
    LoggerConfig loggerConfig;
    loggerConfig.createFileLogger = false;

    try {
        LoggingManager::instance();
        assert(false);
    }
    catch (const logic_error&) { }
    LoggingManager& loggingManager = LoggingManager::initialize(loggerFactory, loggerConfig);
    loggingManager.setDefaultLogLevel(LogLevel::Off);

    LOG_DEBUG(loggingManager.getLogger("tests"), "Starting tests");
    qDebug() << "Starting tests";

    QSettings settings;
    settings.clear();
    auto retCode = Catch::Session().run(argc, const_cast<char const* const* const>(argv));

    settings.clear();
    return retCode;
}
