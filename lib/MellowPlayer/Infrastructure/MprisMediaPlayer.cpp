#include <QtCore>
#ifdef Q_OS_LINUX
#include <QtDBus/QDBusConnection>
#include <QtQuick/QQuickWindow>
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

MprisMediaPlayer::MprisMediaPlayer(IPlayer& player, UseCases::LocalAlbumArt& localAlbumArt, QQuickWindow* window,
                                   LoggingManager& loggingManager)
    : logger(loggingManager.getLogger("MprisMediaPlayer")),
      mpris2Root(new Mpris2Root(window, this)),
      mpris2Player(new Mpris2Player(player, localAlbumArt, this)) {
}

MprisMediaPlayer::~MprisMediaPlayer() {
#ifdef Q_OS_LINUX
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(SERVICE_NAME);
#endif
}

bool MprisMediaPlayer::startService() {
#ifdef Q_OS_LINUX
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME) ||
        !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, this)) {
        LOG_WARN(logger, "failed to register service on the session bus: " << SERVICE_NAME);
        LOG_WARN(logger, "failed to register object on the session bus: " << OBJECT_NAME);
        return false;
    }

    LOG_INFO(logger, "mpris service started: " << SERVICE_NAME.toStdString());
#endif

    return true;
}
