
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

bool QmlMainWindow::load() {
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/MellowPlayer/Presentation/qml/main.qml")));
    auto rootObjects = qmlApplicationEngine.rootObjects();
    if (rootObjects.count() && rootObjects.first() != nullptr)
        window = qobject_cast<QQuickWindow*>(rootObjects.first());
    return window != nullptr;
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
