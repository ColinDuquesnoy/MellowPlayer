#include <QtCore>
#ifdef Q_OS_LINUX
#include <QtDBus/QDBusConnection>
#include <QtQuick/QQuickWindow>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "Mpris/Mpris2Root.hpp"
#include "Mpris/Mpris2Player.hpp"
#include "MprisService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

QString MprisService::SERVICE_NAME = "org.mpris.MediaPlayer2.";

QString MprisService::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisService::MprisService(IPlayer& player,
                           ILocalAlbumArtService& localAlbumArt,
                           IMainWindow& window,
                           IQtApplication& application)
    : logger(LoggingManager::instance().getLogger("Mpris")),
      parent(make_unique<QObject>()),
      mpris2Root(new Mpris2Root(window, application, parent.get())),
      mpris2Player(new Mpris2Player(player, localAlbumArt, parent.get())),
      serviceName(SERVICE_NAME + qApp->applicationName()){

}

MprisService::~MprisService() {
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(serviceName);
}

bool MprisService::start() {
    if (!QDBusConnection::sessionBus().registerService(serviceName) ||
        !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, parent.get())) {
        LOG_WARN(logger, "failed to register service on the session bus: " + serviceName);
        LOG_WARN(logger, "failed to register object on the session bus: " + OBJECT_NAME);
        return false;
    }
    LOG_INFO(logger, "service started: " + serviceName);
    return true;
}

#endif