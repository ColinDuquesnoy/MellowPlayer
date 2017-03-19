#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/UseCases.hpp>
#include "../ViewModels/StreamingServicesViewModel.hpp"
#include "../ViewModels/StyleViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class QmlMainWindow: public QObject, public UseCases::IMainWindow {
    Q_OBJECT
public:
    QmlMainWindow(StreamingServicesViewModel& streamingServices,
                  StyleViewModel& style,
                  UseCases::IPlayer& player,
                  UseCases::ILocalAlbumArtService& albumArt,
                  UseCases::IApplicationSettings& applicationSettings);
    bool load() override;
    void show() override;
    void hide() override;

private:
    QmlMainWindow(const QmlMainWindow&) = delete;
    QmlMainWindow operator=(const QmlMainWindow&) = delete;
    bool eventFilter(QObject *object, QEvent *event);

    QQuickWindow* window;
    UseCases::ILogger& logger;
    UseCases::IApplicationSettings& applicationSettings;
    StreamingServicesViewModel& streamingServices;
    QQmlApplicationEngine qmlApplicationEngine;
};

END_MELLOWPLAYER_NAMESPACE
