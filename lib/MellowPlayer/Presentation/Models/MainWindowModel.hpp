#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/UseCases/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/Presentation/Models/ClipBoardModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/SettingsModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Settings)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IQtApplication)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ApplicationModel;
class ListeningHistoryModel;
class StreamingServicesModel;
class StreamingServiceStyleModel;

class MainWindowModel: public QObject, public UseCases::IMainWindow {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
public:
    MainWindowModel(StreamingServicesModel& streamingServicesModel,
                    ListeningHistoryModel& listeningHistoryModel,
                    StreamingServiceStyleModel& pluginStyleModel,
                    UseCases::IQtApplication& qtApp,
                    UseCases::IPlayer& player,
                    UseCases::ILocalAlbumArtService& albumArt,
                    UseCases::Settings& settings);
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
    UseCases::ILogger& logger;
    UseCases::Settings& settings;
    StreamingServicesModel& streamingServices;
    ListeningHistoryModel& listeningHistory;
    QQmlApplicationEngine qmlApplicationEngine;
    ClipBoardModel clipBoardModel;
    SettingsModel settingsModel;
};

END_MELLOWPLAYER_NAMESPACE
