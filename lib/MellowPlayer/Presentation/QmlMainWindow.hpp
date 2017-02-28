#pragma once

#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/UseCases.hpp>
#include "ViewModels/StreamingServicesViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class QmlMainWindow: public UseCases::IMainWindow {
public:
    QmlMainWindow(StreamingServicesViewModel& streamingServices,
                  UseCases::IPlayer& player, UseCases::LocalAlbumArt& albumArt);
    void load() override;
    void show() override;
    void hide() override;

private:
    QmlMainWindow(const QmlMainWindow&) = delete;
    QmlMainWindow operator=(const QmlMainWindow&) = delete;
    QQuickWindow* window;
    QQmlApplicationEngine qmlApplicationEngine;

};

END_MELLOWPLAYER_NAMESPACE
