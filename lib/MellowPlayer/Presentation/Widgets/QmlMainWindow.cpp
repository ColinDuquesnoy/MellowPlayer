#include <QtWebEngine>
#include <QMessageBox>
#include <MellowPlayer/UseCases/Interfaces/ILocalAlbumArtService.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Player/Player.hpp>
#include <MellowPlayer/UseCases/Settings/ApplicationSettings.hpp>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServiceStyleModel.hpp>
#include "QmlMainWindow.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

QmlMainWindow::QmlMainWindow(StreamingServicesModel& streamingServicesModel,
                             ListeningHistoryModel& listeningHistoryModel,
                             StreamingServiceStyleModel& pluginStyleModel,
                             IPlayer& player,
                             ILocalAlbumArtService& albumArt,
                             ApplicationSettings& applicationSettings) :
        window(nullptr), logger(LoggingManager::instance().getLogger("QmlMainWindow")),
        applicationSettings(applicationSettings), streamingServices(streamingServicesModel),
        listeningHistory(listeningHistoryModel) {
    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    auto context = qmlApplicationEngine.rootContext();
    context->setContextProperty("streamingServices", &streamingServicesModel);
    context->setContextProperty("listeningHistory", &listeningHistoryModel);
    context->setContextProperty("style", &pluginStyleModel);
    context->setContextProperty("player", &player);
    context->setContextProperty("albumArt", &albumArt);
    context->setContextProperty("clipboard", &clipBoardModel);
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
            Setting& setting = applicationSettings.getSetting("private/show-close-to-tray-message");
            bool showMessage = setting.getValue().toBool();
            if (showMessage) {
                // todo: send signal to qml window to show a QML popup instead
                QMessageBox::information(nullptr, tr("Close to system tray"),
                                         tr("The program will keep running in the system tray.<br><br>"
                                                    "To terminate the program, choose <b>Quit</b> in the context menu of the "
                                                    "system tray icon.<br><br>"
                                                    "To restore the window, double click on the system tray icon."));
                setting.setValue(false);
            }
            hide(); // todo hide should be done from QML
            return true;
        }
    }
    return QObject::eventFilter(object, event);
}
