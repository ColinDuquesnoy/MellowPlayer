#define CATCH_CONFIG_RUNNER
#include <stdexcept>
#include "catch.hpp"
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <MellowPlayer/Infrastructure/Logging/SpdLoggerFactory.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/Presentation/QtWebApplication.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
using namespace std;

int main(int argc, char* argv[])
{
#ifdef Q_OS_WIN32
    Q_INIT_RESOURCE(presentation);
#endif
    QtWebApplication webApplication(argc, argv);

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
    loggingManager.setDefaultLogLevel(LogLevel::Warning);
    LOG_DEBUG(loggingManager.getLogger("tests"), "Starting tests");
    qDebug() << "Starting tests";

    auto retCode = Catch::Session().run(argc, const_cast<char const* const* const>(argv));

    settings.clear();
    return retCode;
}