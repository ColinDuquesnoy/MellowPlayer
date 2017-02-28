
#include "QmlMainWindow.hpp"
#include <QQmlContext>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

QmlMainWindow::QmlMainWindow(StreamingServicesViewModel& streamingServices, IPlayer& player, LocalAlbumArt& albumArt):
        window(nullptr) {
    qmlRegisterUncreatableType<Player>("MellowPlayer", 1, 0, "Player", "Player cannot be instantiated from QML");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<Song*>("Entities::Song*");
    qmlApplicationEngine.rootContext()->setContextProperty("streamingServices", &streamingServices);
    qmlApplicationEngine.rootContext()->setContextProperty("player", &player);
    qmlApplicationEngine.rootContext()->setContextProperty("albumArt", &albumArt);
}

void QmlMainWindow::load() {
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    window = qobject_cast<QQuickWindow*>(qmlApplicationEngine.rootObjects().first());
}

void QmlMainWindow::show() {
    if (window != nullptr) {
        window->raise();
        window->show();
    }
}

void QmlMainWindow::hide() {
    if (window != nullptr) {
        window->hide();
    }
}
