#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <MellowPlayer/Logging.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <MellowPlayer/Infrastructure.hpp>

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

int main(int argc, char* argv[])
{
#ifdef Q_OS_WIN32
    Q_INIT_RESOURCE(presentation);
#endif

    // Init Qt Application
    QGuiApplication qtApp(argc, argv);
    qtApp.setApplicationDisplayName("MellowPlayer");
    qtApp.setApplicationName("MellowPlayer3");
    qtApp.setApplicationVersion(MELLOWPLAYER_VERSION);
    qtApp.setOrganizationDomain("org.mellowplayer");
    qtApp.setOrganizationName("MellowPlayer");
    QtWebEngine::initialize();
    QQmlApplicationEngine qmlApplicationEngine;

    // Init logging system
    SpdLoggerFactory loggerFactory;
    LoggingManager& loggingManager = LoggingManager::initialize(loggerFactory);
    loggingManager.setDefaultLogLevel(LogLevel::Debug);
    ILogger& logger = loggingManager.getLogger("main");
    LOG_INFO(logger, "-------------------------------------------------------------------------------");
    LOG_INFO(logger, "MellowPlayer v" << MELLOWPLAYER_VERSION << " started");
    LOG_INFO(logger, "Log directory: " + FileHelper::logDirectory());

    // Init systems
    StreamingServicesLoader streamingServicesLoader(loggingManager);
    StreamingServicesManager streamingServicesManager(streamingServicesLoader);
    PlayerProxy player(streamingServicesManager);
    StreamingServicesViewModel streamingServices(streamingServicesManager);

    // Make c++ objects available to QML
    qmlApplicationEngine.rootContext()->setContextProperty("streamingServices", &streamingServices);
    qmlApplicationEngine.rootContext()->setContextProperty("player", &player);
    qmlRegisterUncreatableType<Player>("MellowPlayer", 1, 0, "Player", "Player cannot be instantiated from QML");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<Song*>("Entities::Song*");

    // Load qml application
    LOG_TRACE(logger, "Loading qml application");
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    LOG_TRACE(logger, "Qml application loaded");

    LOG_TRACE(logger, "Running")
    return qtApp.exec();
}
