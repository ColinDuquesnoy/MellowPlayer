#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/UseCases.hpp>
#include "../ViewModels/StreamingServicesViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class QmlMainWindow: public QObject, public UseCases::IMainWindow {
    Q_OBJECT
public:
    QmlMainWindow(StreamingServicesViewModel& streamingServices,
                  UseCases::IPlayer& player,
                  UseCases::LocalAlbumArt& albumArt,
                  UseCases::IApplicationSettings& applicationSettings);
    bool load() override;
    void show() override;
    void hide() override;

private:
    bool eventFilter(QObject *object, QEvent *event);

    QmlMainWindow(const QmlMainWindow&) = delete;
    QmlMainWindow operator=(const QmlMainWindow&) = delete;
    QQuickWindow* window;
    UseCases::IApplicationSettings& applicationSettings;
    QQmlApplicationEngine qmlApplicationEngine;

};

END_MELLOWPLAYER_NAMESPACE
