#include <QtWebEngine>
#include <QMessageBox>
#include <QQuickStyle>
#include <MellowPlayer/Application/Utils/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StyleViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include "MainWindowViewModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

MainWindowViewModel::MainWindowViewModel(StreamingServicesViewModel& streamingServicesModel,
                                 ListeningHistoryViewModel& listeningHistoryModel,
                                 StyleViewModel& serviceStyleModel,
                                 IQtApplication& qtApp,
                                 IPlayer& player,
                                 Settings& settings) :
        logger(LoggingManager::instance().getLogger("MainWindowViewModel")),
        settings(settings), streamingServices(streamingServicesModel),
        listeningHistory(listeningHistoryModel), settingsModel(settings) {
    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "SettingKey",
                                           "SettingKey cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "MainPageViewModel",
                                           "MainPageViewModel cannot be instantiated from QML");
    auto context = qmlApplicationEngine.rootContext();
    context->setContextProperty("_streamingServices", &streamingServicesModel);
    context->setContextProperty("_listeningHistory", &listeningHistoryModel);
    context->setContextProperty("_style", &serviceStyleModel);
    context->setContextProperty("_player", &player);
    context->setContextProperty("_clipboard", &clipBoardModel);
    context->setContextProperty("_settings", &settingsModel);
    context->setContextProperty("_window", this);
    context->setContextProperty("_app", &qtApp);

}

bool MainWindowViewModel::load() {
    LOG_TRACE(logger, "loading");
    QQuickStyle::setStyle("Material");
    QtWebEngine::initialize();
    streamingServices.initialize();
    listeningHistory.initialize();
    qmlApplicationEngine.addImportPath("qrc:/MellowPlayer/Presentation/Views");
    qmlApplicationEngine.load(QUrl("qrc:/MellowPlayer/Presentation/Views/main.qml"));
    LOG_TRACE(logger, "loaded");
    return true;
}

void MainWindowViewModel::show() {
    setVisible(true);
}

void MainWindowViewModel::hide() {
    setVisible(false);
}

void MainWindowViewModel::setVisible(bool value) {
    if (value != visible) {
        visible = value;
        emit visibleChanged();
    }
}

bool MainWindowViewModel::isVisible() const {
    return visible;
}
