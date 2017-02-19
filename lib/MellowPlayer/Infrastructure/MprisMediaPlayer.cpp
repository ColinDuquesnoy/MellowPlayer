#include <QtCore>
#ifdef Q_OS_LINUX
#include <QtDBus/QDBusConnection>
#endif
#include "MprisMediaPlayer.hpp"
#include "Mpris/Mpris2Root.hpp"
#include "Mpris/Mpris2Player.hpp"

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

QString MprisMediaPlayer::SERVICE_NAME = "org.mpris.MediaPlayer2.MellowPlayer3";

QString MprisMediaPlayer::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisMediaPlayer::MprisMediaPlayer(IPlayer& player, UseCases::LocalAlbumArt& localAlbumArt,
                                   LoggingManager& loggingManager)
    : logger(loggingManager.getLogger("MprisMediaPlayer")) {
#ifdef Q_OS_LINUX
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
        LOG_WARN(logger, "failed to register service on the session bus: " << SERVICE_NAME);
        return;
    }

    mpris2Root = new Mpris2Root(this);
    mpris2Player = new Mpris2Player(player, localAlbumArt, this);

    if (!QDBusConnection::sessionBus().registerObject(OBJECT_NAME, this)) {
        LOG_WARN(logger, "failed to register object on the session bus: " << OBJECT_NAME);
        return;
    }

    LOG_INFO(logger, "mpris service started: " << SERVICE_NAME.toStdString());
#endif
}

MprisMediaPlayer::~MprisMediaPlayer() {
#ifdef Q_OS_LINUX
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(SERVICE_NAME);
#endif
}