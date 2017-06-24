#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/Application/Presentation/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Models/ClipBoardModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/SettingsModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILocalAlbumArt)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class QtApplicationModel;
class ListeningHistoryModel;
class StreamingServicesModel;
class StreamingServiceStyleModel;

class MainWindowModel: public QObject, public Application::IMainWindow {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
public:
    MainWindowModel(StreamingServicesModel& streamingServicesModel,
                    ListeningHistoryModel& listeningHistoryModel,
                    StreamingServiceStyleModel& serviceStyleModel,
                    Application::IQtApplication& qtApp,
                    Application::IPlayer& player,
                    Application::ILocalAlbumArt& albumArt,
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
    StreamingServicesModel& streamingServices;
    ListeningHistoryModel& listeningHistory;
    QQmlApplicationEngine qmlApplicationEngine;
    ClipBoardModel clipBoardModel;
    SettingsModel settingsModel;
};

END_MELLOWPLAYER_NAMESPACE
