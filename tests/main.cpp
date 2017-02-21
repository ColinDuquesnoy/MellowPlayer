#define CATCH_CONFIG_RUNNER
#include <stdexcept>
#include "catch.hpp"
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QGuiApplication>
#include <MellowPlayer/Infrastructure.hpp>
#include <MellowPlayer/Logging.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

int main(int argc, char* argv[])
{
    QGuiApplication qtApp(argc, argv);
    qtApp.setApplicationName("MellowPlayer3");
    qtApp.setApplicationVersion(MELLOWPLAYER_VERSION);
    qtApp.setOrganizationDomain("org.mellowplayer");
    qtApp.setOrganizationName("MellowPlayer");

    QSettings settings;
    settings.clear();

    SpdLoggerFactory loggerFactory;
    LoggerConfig loggerConfig;
    loggerConfig.createFileLogger = false;

    try {
        auto& loggingManager = LoggingManager::instance();
        assert(false);
    }
    catch (const logic_error& e) {
        assert(e.what() == string("LoggingManager::instance called before LoggingManager::initialize!"));
    }
    LoggingManager& loggingManager = LoggingManager::initialize(loggerFactory, loggerConfig);
    loggingManager.setDefaultLogLevel(LogLevel::Off);
    LOG_DEBUG(loggingManager.getLogger("tests"), "Starting tests");
    qDebug() << "Starting tests";

    return Catch::Session().run(argc, const_cast<char const* const* const>(argv));
}