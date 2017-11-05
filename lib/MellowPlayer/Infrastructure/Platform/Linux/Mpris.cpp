#include <QtCore>

#ifdef Q_OS_LINUX

#include "MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Player.hpp"
#include "MellowPlayer/Infrastructure/Platform/Linux/Mpris/Mpris2Root.hpp"
#include "Mpris.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>


using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

QString Mpris::SERVICE_NAME = "org.mpris.MediaPlayer2.";

QString Mpris::OBJECT_NAME = "/org/mpris/MediaPlayer2";

Mpris::Mpris(IPlayer& player, ILocalAlbumArt& localAlbumArt, IMainWindow& window, IQtApplication& application)
        : logger_(LoggingManager::logger("Mpris")),
          parent_(make_unique<QObject>()),
          mpris2Root_(new Mpris2Root(window, application, parent_.get())),
          mpris2Player_(new Mpris2Player(player, localAlbumArt, parent_.get())),
          serviceName_(SERVICE_NAME + qApp->applicationName())
{
}

Mpris::~Mpris()
{
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(serviceName_);
}

bool Mpris::start()
{
    if (!QDBusConnection::sessionBus().registerService(serviceName_) || !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, parent_.get())) {
        LOG_WARN(logger_, "failed to register service on the session bus: " + serviceName_);
        LOG_WARN(logger_, "failed to register object on the session bus: " + OBJECT_NAME);
        return false;
    }
    LOG_DEBUG(logger_, "service started: " + serviceName_);
    return true;
}

#endif