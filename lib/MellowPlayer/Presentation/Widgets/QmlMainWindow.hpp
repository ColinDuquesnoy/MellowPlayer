#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/UseCases/Interfaces/IMainWindow.hpp>
#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ISettingsProvider)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryViewModel;
class StreamingServicesViewModel;
class StyleViewModel;

class QmlMainWindow: public QObject, public UseCases::IMainWindow {
    Q_OBJECT
public:
    QmlMainWindow(StreamingServicesViewModel& streamingServices,
                  ListeningHistoryViewModel& listeningHistory,
                  StyleViewModel& style,
                  UseCases::IPlayer& player,
                  UseCases::ILocalAlbumArtService& albumArt,
                  UseCases::ISettingsProvider& applicationSettings);
    bool load() override;
    void show() override;
    void hide() override;

private:
    QmlMainWindow(const QmlMainWindow&) = delete;
    QmlMainWindow operator=(const QmlMainWindow&) = delete;
    bool eventFilter(QObject *object, QEvent *event) override;

    QQuickWindow* window;
    UseCases::ILogger& logger;
    UseCases::ISettingsProvider& applicationSettings;
    StreamingServicesViewModel& streamingServices;
    ListeningHistoryViewModel& listeningHistory;
    QQmlApplicationEngine qmlApplicationEngine;
    ClipBoardViewModel clipBoardViewModel;
};

END_MELLOWPLAYER_NAMESPACE
