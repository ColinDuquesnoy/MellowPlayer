#include <QtCore>

#ifdef Q_OS_LINUX

#include <QtDBus/QDBusConnection>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Root.hpp"
#include "MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Player.hpp"
#include "MprisController.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace std;

QString MprisController::SERVICE_NAME = "org.mpris.MediaPlayer2.";

QString MprisController::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisController::MprisController(IPlayer& player,
                           ILocalAlbumArt& localAlbumArt,
                           IMainWindow& window,
                           IQtApplication& application)
    : logger(LoggingManager::instance().getLogger("Mpris")),
      parent(make_unique<QObject>()),
      mpris2Root(new Mpris2Root(window, application, parent.get())),
      mpris2Player(new Mpris2Player(player, localAlbumArt, parent.get())),
      serviceName(SERVICE_NAME + qApp->applicationName()){

}

MprisController::~MprisController() {
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(serviceName);
}

bool MprisController::start() {
    if (!QDBusConnection::sessionBus().registerService(serviceName) ||
        !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, parent.get())) {
        LOG_WARN(logger, "failed to register service on the session bus: " + serviceName);
        LOG_WARN(logger, "failed to register object on the session bus: " + OBJECT_NAME);
        return false;
    }
    LOG_DEBUG(logger, "service started: " + serviceName);
    return true;
}

#endif