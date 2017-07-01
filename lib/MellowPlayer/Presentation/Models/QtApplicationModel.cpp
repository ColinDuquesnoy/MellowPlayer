#include <QtWebEngine>
#include <QWebEngineProfile>
#include <MellowPlayer/Application/Player/Song.hpp>
#include <MellowPlayer/Application/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "MellowPlayer/Presentation/Utils/IconProvider.hpp"
#include <MellowPlayer/Presentation/Models/Settings/Types/SettingModel.hpp>
#include "QtApplicationModel.hpp"


USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

QtApplicationModel::QtApplicationModel(int &argc, char **argv, const QString& appName) :
        qtApp(argc, argv){
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

    qRegisterMetaType<Song*>("Application::Song*");
    qRegisterMetaType<Song*>("Song*");
    qRegisterMetaType<StreamingService*>("Application::StreamingService*");
    qRegisterMetaType<StreamingService*>("StreamingService*");
    qRegisterMetaType<ListeningHistoryEntry>("Application::ListeningHistoryEntry");
    qRegisterMetaType<ListeningHistoryEntry>("ListeningHistoryEntry");
    qRegisterMetaType<Player*>("Application::Player*");
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
    emit quitRequested();
}

void QtApplicationModel::quit() {
    qtApp.exit(0);
}
