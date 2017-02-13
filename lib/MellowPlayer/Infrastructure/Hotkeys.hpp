#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

class QxtGlobalShortcut;

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Hotkeys: public QObject {
    Q_OBJECT
public:
    Hotkeys(UseCases::IPlayer& player);

private slots:
    void togglePlayPause();
    void next();
    void previous();
    void toggleFavoriteSong();

private:
    UseCases::IPlayer& player;
    QxtGlobalShortcut* playShortcut;
    QxtGlobalShortcut* nextShortcut;
    QxtGlobalShortcut* previousShortcut;
    QxtGlobalShortcut* favoriteShortcut;
};

END_MELLOWPLAYER_NAMESPACE
