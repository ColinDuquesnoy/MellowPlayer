#define CATCH_CONFIG_RUNNER
#include <QString>
#include <QtCore/QCoreApplication>
#include <Infrastructure.hpp>
#include <UseCases.hpp>
#include "catch.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

int main(int argc, char* argv[])
{
    QCoreApplication qtApp(argc, argv);
    qtApp.setApplicationName("MellowPlayer3");
    qtApp.setApplicationVersion(MELLOWPLAYER_VERSION);
    qtApp.setOrganizationDomain("org.mellowplayer");
    qtApp.setOrganizationName("MellowPlayer");

    SpdLoggerFactory loggerFactory;
    LoggerConfig loggerConfig;
    loggerConfig.createFileLogger = false;
    LoggingManager& loggingManager = LoggingManager::initialize(loggerFactory);
    LOG_DEBUG(loggingManager.getLogger("tests"), "Starting tests");

    return Catch::Session().run(argc, const_cast<char const* const* const>(argv));
}