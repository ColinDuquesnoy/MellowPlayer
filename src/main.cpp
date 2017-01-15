#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <UseCases/Logging.hpp>
#include <Infrastructure/Logging.hpp>
#include <Infrastructure/System/FileHelper.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

int main(int argc, char* argv[])
{
    QGuiApplication qtApp(argc, argv);
    qtApp.setApplicationDisplayName("MellowPlayer");
    qtApp.setApplicationName("MellowPlayer3");
    qtApp.setApplicationVersion(MELLOWPLAYER_VERSION);
    qtApp.setOrganizationDomain("org.mellowplayer");
    qtApp.setOrganizationName("MellowPlayer");

    SpdLoggerFactory loggerFactory;
    LoggingManager& loggingManager = LoggingManager::initialize(loggerFactory);
    loggingManager.setDefaultLogLevel(LogLevel::Trace);

    LoggerConfig loggerConfig; loggerConfig.showFileAndLine = false;
    ILogger& logger = loggingManager.getLogger("main", loggerConfig);
    LOG_INFO(logger, "-------------------------------------------------------------------------------");
    LOG_INFO(logger, "MellowPlayer v" << MELLOWPLAYER_VERSION << " started");
    LOG_INFO(logger, "Log directory: " << FileHelper::logDirectory());

    QtWebEngine::initialize();
    QQmlApplicationEngine qmlApplicationEngine;
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return qtApp.exec();
}
