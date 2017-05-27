#include <QtWebEngine>
#include <QWebEngineProfile>
#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/UseCases/Player/Player.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include "MellowPlayer/Presentation/IconProvider.hpp"
#include <MellowPlayer/Presentation/Models/Settings/Types/SettingModel.hpp>
#include "QtApplicationModel.hpp"


USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

QtApplicationModel::QtApplicationModel(int &argc, char **argv, const QString& appName) :
        qtApp(argc, argv),
        logger(LoggingManager::instance().getLogger("QtApplicationModel")) {
    qtApp.setApplicationDisplayName("MellowPlayer");
    qtApp.setApplicationName(appName);
    qtApp.setApplicationVersion(MELLOWPLAYER_VERSION);
    qtApp.setOrganizationDomain("org.mellowplayer");
    qtApp.setOrganizationName("MellowPlayer");
    qtApp.setWindowIcon(IconProvider::windowIcon());

    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/Resources/fonts/Roboto/Roboto-ThinItalic.ttf");

    qRegisterMetaType<Song*>("Entities::Song*");
    qRegisterMetaType<Song*>("Song*");
    qRegisterMetaType<StreamingServicePlugin*>("Entities::StreamingServicePlugin*");
    qRegisterMetaType<StreamingServicePlugin*>("StreamingServicePlugin*");
    qRegisterMetaType<ListeningHistoryEntry>("Entities::ListeningHistoryEntry");
    qRegisterMetaType<ListeningHistoryEntry>("ListeningHistoryEntry");
    qRegisterMetaType<Player*>("UseCases::Player*");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<SettingModel*>("Presentation::SettingModel*");
    qRegisterMetaType<SettingModel*>("SettingModel*");
}

int QtApplicationModel::run() {
    return qtApp.exec();
}

void QtApplicationModel::clearCache() const
{
    QWebEngineProfile profile("Default");
    profile.clearHttpCache();
    QDir cacheDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    qDebug() << "removing cache directory: " << cacheDir;
    cacheDir.removeRecursively();
}

void QtApplicationModel::clearCookies() const
{
    QWebEngineProfile profile("Default");
    QDir storageDir(profile.persistentStoragePath());
    qDebug() << "removing persistent storage directory: " << storageDir;
    storageDir.removeRecursively();
}

void QtApplicationModel::restart() {
    quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void QtApplicationModel::requestQuit() {
    LOG_TRACE(logger, "quit requested");
    emit quitRequested();
}

void QtApplicationModel::quit() {
    LOG_TRACE(logger, "quitting");
    qtApp.exit(0);
}
