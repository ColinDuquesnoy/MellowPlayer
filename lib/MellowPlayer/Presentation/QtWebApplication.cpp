#include <QtWebEngine>
#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/UseCases/Player/Player.hpp>
#include "IconProvider.hpp"
#include "QtWebApplication.hpp"
#include "MellowPlayer/Presentation/Models/Settings/Types/SettingModel.hpp"
#include "Widgets/QmlMainWindow.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

QtWebApplication::QtWebApplication(int &argc, char **argv) :
    QApplication(argc, argv) {
    setApplicationDisplayName("MellowPlayer");
    setApplicationName("MellowPlayer3");
    setApplicationVersion(MELLOWPLAYER_VERSION);
    setOrganizationDomain("org.mellowplayer");
    setOrganizationName("MellowPlayer");
    setWindowIcon(IconProvider::windowIcon());

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

int QtWebApplication::run() {
    return exec();
}

void QtWebApplication::quit() {
    exit(0);
}
