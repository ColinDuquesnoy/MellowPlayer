#include <QtCore>
#ifdef Q_OS_LINUX
#include <QtDBus/QDBusConnection>
#include <QtQuick/QQuickWindow>
#include "Mpris/Mpris2Root.hpp"
#include "Mpris/Mpris2Player.hpp"
#include "MprisMediaPlayer.hpp"

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

QString MprisMediaPlayer::SERVICE_NAME = "org.mpris.MediaPlayer2.MellowPlayer3";

QString MprisMediaPlayer::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisMediaPlayer::MprisMediaPlayer(IPlayer& player, UseCases::LocalAlbumArt& localAlbumArt, QQuickWindow* window,
                                   LoggingManager& loggingManager)
    : logger(loggingManager.getLogger("MprisMediaPlayer")),
      parent(make_unique<QObject>()),
      mpris2Root(new Mpris2Root(window, parent.get())),
      mpris2Player(new Mpris2Player(player, localAlbumArt, parent.get())) {

}

MprisMediaPlayer::~MprisMediaPlayer() {
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(SERVICE_NAME);
}

bool MprisMediaPlayer::startService() {
    if (QDBusConnection::sessionBus().isConnected()) {
        if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME) ||
            !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, parent.get())) {
            LOG_WARN(logger, "failed to register service on the session bus: " << SERVICE_NAME);
            LOG_WARN(logger, "failed to register object on the session bus: " << OBJECT_NAME);
            return false;
        }
        LOG_INFO(logger, "mpris service started: " << SERVICE_NAME.toStdString());
    } else {
        LOG_WARN(logger, "failed to start mprice service, unable to session bus");
    }

    return true;
}

#endif