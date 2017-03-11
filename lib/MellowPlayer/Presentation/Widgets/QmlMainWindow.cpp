#include <QtWebEngine>
#include <QQmlContext>
#include <QMessageBox>
#include "QmlMainWindow.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

QmlMainWindow::QmlMainWindow(StreamingServicesViewModel& streamingServices, IPlayer& player, LocalAlbumArtService& albumArt,
                             IApplicationSettings& applicationSettings) :
        window(nullptr), applicationSettings(applicationSettings) {
    qmlRegisterUncreatableType<Player>("MellowPlayer", 1, 0, "Player", "Player cannot be instantiated from QML");
    qmlApplicationEngine.rootContext()->setContextProperty("streamingServices", &streamingServices);
    qmlApplicationEngine.rootContext()->setContextProperty("player", &player);
    qmlApplicationEngine.rootContext()->setContextProperty("albumArt", &albumArt);
}

bool QmlMainWindow::load() {
    QtWebEngine::initialize();
    qmlApplicationEngine.load(QUrl(QLatin1String("qrc:/MellowPlayer/Presentation/resources/qml/main.qml")));
    auto rootObjects = qmlApplicationEngine.rootObjects();
    if (rootObjects.count() && rootObjects.first() != nullptr) {
        window = qobject_cast<QQuickWindow*>(rootObjects.first());
        window->installEventFilter(this);
    }
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

bool QmlMainWindow::eventFilter(QObject* object, QEvent* event) {
    if (object == window) {
        if (event->type() == QEvent::Close) {
            if (applicationSettings.getShowCloseToSysemTrayMessage()) {
                QMessageBox::information(nullptr, tr("Close to system tray"),
                                         tr("The program will keep running in the system tray.<br><br>"
                                            "To terminate the program, choose <b>Quit</b> in the context menu of the "
                                            "system tray icon.<br><br>"
                                            "To restore the window, double click on the system tray icon."));
                applicationSettings.setShowCloseToSystemTrayMessage(false);
            }
            hide();
            return true;
        }
    }
    return QObject::eventFilter(object, event);
}
