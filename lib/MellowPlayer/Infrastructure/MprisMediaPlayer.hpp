#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

class QQuickWindow;

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Root;
class Mpris2Player;

class MprisMediaPlayer: public QObject {
    Q_OBJECT
public:
    MprisMediaPlayer(UseCases::IPlayer& player, UseCases::LocalAlbumArt& localAlbumArt,
                     Logging::LoggingManager& loggingManager);
    ~MprisMediaPlayer();

    void setWindow(QQuickWindow* window);

private:
    static QString SERVICE_NAME;
    static QString OBJECT_NAME;

    Logging::ILogger& logger;
    Mpris2Root* mpris2Root;
    Mpris2Player* mpris2Player;
};

END_MELLOWPLAYER_NAMESPACE