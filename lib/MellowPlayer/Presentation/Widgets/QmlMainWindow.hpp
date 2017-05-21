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

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryModel;
class StreamingServicesModel;
class StreamingServiceStyleModel;

class QmlMainWindow: public QObject, public UseCases::IMainWindow {
    Q_OBJECT
public:
    QmlMainWindow(StreamingServicesModel& streamingServicesModel,
                  ListeningHistoryModel& listeningHistoryModel,
                  StreamingServiceStyleModel& pluginStyleModel,
                  UseCases::IPlayer& player,
                  UseCases::ILocalAlbumArtService& albumArt,
                  UseCases::Settings& settings);
    bool load() override;
    void show() override;
    void hide() override;

private:
    bool eventFilter(QObject *object, QEvent *event) override;

    QQuickWindow* window;
    UseCases::ILogger& logger;
    UseCases::Settings& settings;
    StreamingServicesModel& streamingServices;
    ListeningHistoryModel& listeningHistory;
    QQmlApplicationEngine qmlApplicationEngine;
    ClipBoardModel clipBoardModel;
    SettingsModel settingsModel;
};

END_MELLOWPLAYER_NAMESPACE
