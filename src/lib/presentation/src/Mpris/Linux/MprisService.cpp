#include <QtCore>

#include <MellowPlayer/Presentation/Mpris/Linux/MprisService.hpp>
#include "MellowPlayer/Presentation/Mpris/Linux/Mpris2Player.hpp"
#include "MellowPlayer/Presentation/Mpris/Linux/Mpris2Root.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Presentation/IMainWindow.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace std;

QString MprisService::SERVICE_NAME = "org.mpris.MediaPlayer2.";
QString MprisService::OBJECT_NAME = "/org/mpris/MediaPlayer2";

MprisService::MprisService(IPlayer& player, ILocalAlbumArt& localAlbumArt, IMainWindow& window)
        : logger_(Loggers::logger("Mpris")),
          parent_(make_unique<QObject>()),
          mpris2Root_(new Mpris2Root(window, parent_.get())),
          mpris2Player_(new Mpris2Player(player, localAlbumArt, parent_.get())),
          serviceName_(SERVICE_NAME + qApp->applicationName())
{

}

MprisService::~MprisService()
{
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(serviceName_);
}

bool MprisService::start()
{
    if (!QDBusConnection::sessionBus().registerService(serviceName_) || !QDBusConnection::sessionBus().registerObject(OBJECT_NAME, parent_.get())) {
        LOG_WARN(logger_, "failed to register service on the session bus: " + serviceName_);
        LOG_WARN(logger_, "failed to register object on the session bus: " + OBJECT_NAME);
        return false;
    }
    LOG_INFO(logger_, "service started: " + serviceName_);
    return true;
}

