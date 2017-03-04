#include <QtWebEngine>
#include "QtWebApplication.hpp"
#include "QmlMainWindow.hpp"

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
    setWindowIcon(QIcon::fromTheme("mellowplayer", QIcon("://MellowPlayer/Presentation/icons/mellowplayer.png")));

    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/MellowPlayer/Presentation/fonts/Roboto/Roboto-ThinItalic.ttf");

    QtWebEngine::initialize();
}

int QtWebApplication::run() {
    return exec();
}

void QtWebApplication::quit() {
    exit(0);
}
