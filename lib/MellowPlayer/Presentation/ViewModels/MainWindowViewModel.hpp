#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ApplicationViewModel;
class ListeningHistoryViewModel;
class StreamingServicesViewModel;
class StyleViewModel;

class MainWindowViewModel: public QObject, public Application::IMainWindow {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
public:
    MainWindowViewModel(StreamingServicesViewModel& streamingServicesModel,
                        ListeningHistoryViewModel& listeningHistoryModel,
                        StyleViewModel& serviceStyleModel,
                        Application::IQtApplication& qtApp,
                        Application::IPlayer& player,
                        Application::Settings& settings);
    bool load() override;
    void show() override;
    void hide() override;
    bool isVisible() const;

signals:
    void visibleChanged();

private slots:
    void setVisible(bool value);

private:
    bool visible = false;
    Application::ILogger& logger;
    Application::Settings& settings;
    StreamingServicesViewModel& streamingServices;
    ListeningHistoryViewModel& listeningHistory;
    QQmlApplicationEngine qmlApplicationEngine;
    ClipBoardViewModel clipBoardModel;
    SettingsViewModel settingsModel;
};

END_MELLOWPLAYER_NAMESPACE
