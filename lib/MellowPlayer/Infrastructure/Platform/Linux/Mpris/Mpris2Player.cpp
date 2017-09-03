#include "Mpris2Player.hpp"
#include <MellowPlayer/Application/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Logging/ILogger.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Player/Song.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

const qlonglong Mpris2Player::SEC_TO_MICROSEC = 1000000;
const qlonglong Mpris2Player::SEEK_DELTA_LIMIT = Mpris2Player::SEC_TO_MICROSEC * 2;

Mpris2Player::Mpris2Player(IPlayer& player, ILocalAlbumArt& localAlbumArt, QObject* parent)
        : QDBusAbstractAdaptor(parent),
          previousPosition_(0),
          logger_(LoggingManager::logger("Mpris2Player")),
          player_(player),
          localAlbumArt_(localAlbumArt)
{
    connect(&player, &IPlayer::playbackStatusChanged, this, &Mpris2Player::onPlaybackStatusChanged);
    connect(&player, &IPlayer::currentSongChanged, this, &Mpris2Player::onSongChanged);
    connect(&player, &IPlayer::positionChanged, this, &Mpris2Player::onPositionChanged);
    connect(&player, &IPlayer::canSeekChanged, this, &Mpris2Player::onCanSeekChanged);
    connect(&player, &IPlayer::canGoNextChanged, this, &Mpris2Player::onCanGoNextChanged);
    connect(&player, &IPlayer::canGoPreviousChanged, this, &Mpris2Player::onCanGoPreviousChanged);
    connect(&player, &IPlayer::volumeChanged, this, &Mpris2Player::onVolumeChanged);

    connect(&localAlbumArt, &ILocalAlbumArt::urlChanged, this, &Mpris2Player::onArtUrlChanged);
}

QString Mpris2Player::playbackStatus()
{
    auto retVal = statusToString(player_.playbackStatus());
    LOG_TRACE(logger_, "playbackStatus() -> " + retVal);
    return retVal;
}

QString Mpris2Player::loopStatus()
{
    LOG_TRACE(logger_, "loopStatus() -> None");
    return "None";
}

void Mpris2Player::setLoopStatus(const QString&)
{
    LOG_TRACE(logger_, "setLoopStatus() not implemented");
}

bool Mpris2Player::shuffle()
{
    LOG_TRACE(logger_, "shuffle() -> false");
    return false;
}

void Mpris2Player::setShuffle(bool)
{
    LOG_TRACE(logger_, "setShuffle not implemented");
}

double Mpris2Player::volume()
{
    auto retVal = player_.volume();
    LOG_TRACE(logger_, "volume() -> " << retVal);
    return retVal;
}

void Mpris2Player::setVolume(double value)
{
    LOG_TRACE(logger_, "setVolume(" << value << ")");
    player_.setVolume(value);
}

QVariantMap Mpris2Player::metadata()
{
    LOG_TRACE(logger_, "metadata()");
    lastMetadata_ = toXesam(*player_.currentSong());
    return lastMetadata_;
}

double Mpris2Player::minimumRate()
{
    LOG_TRACE(logger_, "minimumRate() -> 1.0");
    return 1.0;
}

double Mpris2Player::maximumRate()
{
    LOG_TRACE(logger_, "maximumRate() -> 1.0");
    return 1.0;
}

double Mpris2Player::rate()
{
    LOG_TRACE(logger_, "rate() -> 1.0");
    return 1.0;
}

void Mpris2Player::setRate(float)
{
    LOG_TRACE(logger_, "setRate() not implemented");
}

qlonglong Mpris2Player::position()
{
    auto pos = static_cast<qlonglong>(player_.position()) * SEC_TO_MICROSEC;
    LOG_TRACE(logger_, "position() -> " << pos);
    return pos;
}

bool Mpris2Player::canGoNext()
{
    auto retVal = player_.canGoNext();
    LOG_TRACE(logger_, "canGoNext() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canGoPrevious()
{
    auto retVal = player_.canGoPrevious();
    LOG_TRACE(logger_, "canGoPrevious() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canPlay()
{
    LOG_TRACE(logger_, "canPlay() -> true");
    return true;
}

bool Mpris2Player::canStop()
{
    LOG_TRACE(logger_, "canStop() -> false");
    return false;
}

bool Mpris2Player::canPause()
{
    LOG_TRACE(logger_, "canPause() -> true");
    return true;
}

bool Mpris2Player::canSeek()
{
    auto retVal = player_.canSeek();
    LOG_TRACE(logger_, "canSeek() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canControl()
{
    LOG_TRACE(logger_, "canControl() -> true");
    return true;
}

void Mpris2Player::PlayPause()
{
    LOG_TRACE(logger_, "PlayPause()");
    player_.togglePlayPause();
}

void Mpris2Player::Play()
{
    LOG_TRACE(logger_, "Play()");
    player_.play();
}

void Mpris2Player::Pause()
{
    LOG_TRACE(logger_, "Pause()");
    player_.pause();
}

void Mpris2Player::Stop()
{
    LOG_TRACE(logger_, "Stop()");
    player_.pause();
}

void Mpris2Player::Next()
{
    LOG_TRACE(logger_, "Next()");
    player_.next();
}

void Mpris2Player::Previous()
{
    LOG_TRACE(logger_, "Previous()");
    player_.previous();
}

void Mpris2Player::Seek(qlonglong position)
{
    LOG_TRACE(logger_, "Seek(" << position << ")");
    qlonglong newPosition = this->position() + position;
    previousPosition_ = 0; // force emit seeked
    player_.seekToPosition(newPosition / SEC_TO_MICROSEC);
}

void Mpris2Player::SetPosition(const QDBusObjectPath&, qlonglong position)
{
    LOG_TRACE(logger_, "SetPosition(" << position << ")");
    previousPosition_ = 0; // force emit seeked
    player_.seekToPosition(position / SEC_TO_MICROSEC);
}

void Mpris2Player::onPlaybackStatusChanged()
{
    LOG_TRACE(logger_, "onPlaybackStatusChanged(" + playbackStatus() + ")");
    QVariantMap map;
    map["PlaybackStatus"] = statusToString(player_.playbackStatus());
    signalPlayerUpdate(map);
}

void Mpris2Player::onSongChanged(Song* song)
{
    LOG_TRACE(logger_, "onSongChanged()");
    if (song != nullptr) {
        QVariantMap map;
        map["Metadata"] = toXesam(*song);
        if (map != lastMetadata_)
            signalPlayerUpdate(map);
        lastMetadata_ = map;
        connect(song, &Song::durationChanged, this, &Mpris2Player::onDurationChanged);
    }
}

void Mpris2Player::onArtUrlChanged()
{
    LOG_TRACE(logger_, "onArtUrlChanged()");
    onSongChanged(player_.currentSong());
}

void Mpris2Player::onPositionChanged()
{
    qlonglong pos = static_cast<qlonglong>(player_.position()) * SEC_TO_MICROSEC;
    if (labs(pos - previousPosition_) > SEEK_DELTA_LIMIT || (previousPosition_ == 0 && pos > 0))
        emit Seeked(pos);
    previousPosition_ = pos;
}

void Mpris2Player::onDurationChanged()
{
    LOG_TRACE(logger_, "onDurationChanged()");
    onSongChanged(player_.currentSong());
}

void Mpris2Player::onCanSeekChanged()
{
    LOG_TRACE(logger_, "onCanSeekChanged()");
    QVariantMap map;
    map["CanSeek"] = player_.canSeek();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoPreviousChanged()
{
    LOG_TRACE(logger_, "onCanGoPreviousChanged()");
    QVariantMap map;
    map["CanGoPrevious"] = player_.canGoPrevious();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoNextChanged()
{
    LOG_TRACE(logger_, "onCanGoNextChanged()");
    QVariantMap map;
    map["CanGoNext"] = player_.canGoNext();
    signalPlayerUpdate(map);
}

void Mpris2Player::onVolumeChanged()
{
    LOG_TRACE(logger_, "onVolumeChanged()");
    QVariantMap map;
    map["Volume"] = player_.volume();
    signalPlayerUpdate(map);
}

QMap<QString, QVariant> Mpris2Player::toXesam(const Song& song)
{
    LOG_TRACE(logger_, "toXesam('" + song.toString() + "')");
    QMap<QString, QVariant> map;
    if (song.isValid()) {
        QStringList artist;
        artist.append(song.artist());
        map["xesam:url"] = song.title();
        map["xesam:artist"] = artist;
        map["xesam:album"] = song.album();
        map["xesam:title"] = song.title();
        if (song.duration())
            map["mpris:length"] = (qlonglong)song.duration() * SEC_TO_MICROSEC;
        else
            map["mpris:length"] = 1;
        QString trackId = QString("/org/mpris/MediaPlayer2/Track/%1").arg(song.uniqueId());
        map["mpris:trackid"] = QVariant(QDBusObjectPath(trackId).path());
        map["mpris:artUrl"] = "file://" + localAlbumArt_.url();
    } else {
        QStringList artist;
        artist.append("");
        map["xesam:url"] = "";
        map["xesam:artist"] = artist;
        map["xesam:album"] = "";
        map["xesam:title"] = "";
        map["mpris:length"] = 0;
        map["mpris:trackid"] = QVariant(QDBusObjectPath("/org/mpris/MediaPlayer2/NoTrack").path());
        map["mpris:artUrl"] = "";
    }
    LOG_TRACE(logger_, "metadata: {" + qMapToString(map) + "\n}");
    return map;
}

QString Mpris2Player::statusToString(PlaybackStatus status)
{
    // a player that is buffering is considered to be paused for mpris, otherwise
    // the player disappear on Plasma 5.
    if (status == PlaybackStatus::Buffering)
        status = PlaybackStatus::Paused;
    switch (status) {
        case PlaybackStatus::Playing:
            return "Playing";
        case PlaybackStatus::Paused:
            return "Paused";
        default:
            return "Stopped";
    }
}

void Mpris2Player::signalPlayerUpdate(const QVariantMap& map)
{
    LOG_TRACE(logger_, "signalPlayerUpdate");
    signalUpdate(map, "org.mpris.MediaPlayer2.Player");
}

void Mpris2Player::signalUpdate(const QVariantMap& map, const QString& interfaceName)
{
    LOG_TRACE(logger_, "signalUpdate");
    if (!map.isEmpty()) {
        QDBusMessage signal = QDBusMessage::createSignal("/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", "PropertiesChanged");
        QVariantList args = QVariantList() << interfaceName << map << QStringList();
        signal.setArguments(args);

        LOG_TRACE(logger_, "PropertiesChanged: {" + qMapToString(map) + "\n}");
        QDBusConnection::sessionBus().send(signal);
    }
}

QString Mpris2Player::qMapToString(const QMap<QString, QVariant>& map)
{
    QString output;
    for (auto it = map.begin(); it != map.end(); ++it) {
        // Format output here.
        output += QString("\n\t%1=%2,").arg(it.key()).arg(it.value().toString());
    }
    return output;
}
