#include "MainWindowViewModel.hpp"
#include <MellowPlayer/Application/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Logging/ILogger.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Settings/SettingKey.hpp>
#include <MellowPlayer/Presentation/ViewModels/ApplicationViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <QtQml/QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QtWebEngine/QtWebEngine>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

MainWindowViewModel::MainWindowViewModel(StreamingServicesControllerViewModel& streamingServicesModel,
                                         ListeningHistoryViewModel& listeningHistoryModel, ThemeViewModel& themeViewModel,
                                         UpdaterViewModel& updaterViewModel, IQtApplication& qtApp, IPlayer& player, Settings& settings)
        : logger_(LoggingManager::logger("MainWindowViewModel")),
          settings_(settings),
          streamingServices_(streamingServicesModel),
          listeningHistory_(listeningHistoryModel),
          settingsViewModel_(settings, themeViewModel),
          updaterViewModel_(updaterViewModel)
{
    qmlRegisterUncreatableType<Player>("MellowPlayer", 3, 0, "Player", "Player cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "SettingKey", "SettingKey cannot be instantiated from QML");
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "MainPageViewModel", "MainPageViewModel cannot be instantiated from QML");
    auto context = qmlApplicationEngine_.rootContext();
    context->setContextProperty("_streamingServices", &streamingServicesModel);
    context->setContextProperty("_listeningHistory", &listeningHistoryModel);
    context->setContextProperty("_theme", &themeViewModel);
    context->setContextProperty("_player", &player);
    context->setContextProperty("_clipboard", &clipBoardModel_);
    context->setContextProperty("_settings", &settingsViewModel_);
    context->setContextProperty("_devTools", &devToolsWindowViewModel);
    context->setContextProperty("_window", this);
    context->setContextProperty("_app", &qtApp);
    context->setContextProperty("_updater", &updaterViewModel);
}

bool MainWindowViewModel::load()
{
    LOG_TRACE(logger_, "loading");
    QQuickStyle::setStyle("Material");
    QtWebEngine::initialize();
    streamingServices_.initialize();
    listeningHistory_.initialize();
    qmlApplicationEngine_.addImportPath("qrc:/MellowPlayer/Presentation/Views");
    qmlApplicationEngine_.load(QUrl("qrc:/MellowPlayer/Presentation/Views/main.qml"));
    updaterViewModel_.check();
    LOG_TRACE(logger_, "loaded");
    return true;
}

void MainWindowViewModel::show()
{
    setVisible(true);
}

void MainWindowViewModel::hide()
{
    setVisible(false);
}

void MainWindowViewModel::setVisible(bool value)
{
    if (value != visible_) {
        visible_ = value;
        emit visibleChanged();
    }
}

bool MainWindowViewModel::isVisible() const
{
    return visible_;
}
