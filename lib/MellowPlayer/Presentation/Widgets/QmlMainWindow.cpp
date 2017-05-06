#include <QtWebEngine>
#include <QQmlContext>
#include <QMessageBox>
#include <MellowPlayer/UseCases/Interfaces/IApplicationSettings.hpp>
#include <MellowPlayer/UseCases/Interfaces/ILocalAlbumArtService.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Player/Player.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StyleViewModel.hpp>
#include "QmlMainWindow.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

QmlMainWindow::QmlMainWindow(StreamingServicesViewModel& streamingServices,
                             ListeningHistoryViewModel& listeningHistory,
                             StyleViewModel& style,
                             IPlayer& player,
                             ILocalAlbumArtService& albumArt,
                             IApplicationSettings& applicationSettings) :
        window(nullptr), logger(LoggingManager::instance().getLogger("QmlMainWindow")),
        applicationSettings(applicationSettings), streamingServices(streamingServices),
        listeningHistory(listeningHistory) {
    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    auto context = qmlApplicationEngine.rootContext();
    context->setContextProperty("streamingServices", &streamingServices);
    context->setContextProperty("listeningHistory", &listeningHistory);
    context->setContextProperty("style", &style);
    context->setContextProperty("player", &player);
    context->setContextProperty("albumArt", &albumArt);
}

bool QmlMainWindow::load() {
    LOG_TRACE(logger, "loading");
    QtWebEngine::initialize();
    streamingServices.initialize();
    listeningHistory.initialize();
    qmlApplicationEngine.addImportPath("qrc:/MellowPlayer/Presentation/Views");
    qmlApplicationEngine.load(QUrl("qrc:/MellowPlayer/Presentation/Views/main.qml"));
    auto rootObjects = qmlApplicationEngine.rootObjects();
    if (rootObjects.count() && rootObjects.first() != nullptr) {
        window = qobject_cast<QQuickWindow*>(rootObjects.first());
        window->installEventFilter(this);
    }
    bool retVal = window != nullptr;
    LOG_TRACE(logger, "loaded: " << retVal);
    return retVal;
}

void QmlMainWindow::show() {
    if (window != nullptr) {
        LOG_DEBUG(logger, "show");
        window->raise();
        window->show();
    }
}

void QmlMainWindow::hide() {
    if (window != nullptr) {
        LOG_DEBUG(logger, "hide");
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
