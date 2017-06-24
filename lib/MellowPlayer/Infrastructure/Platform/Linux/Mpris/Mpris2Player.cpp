#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/ILocalAlbumArt.hpp>
#include <MellowPlayer/Application/Player/Song.hpp>
#include "Mpris2Player.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

const qlonglong Mpris2Player::SEC_TO_MICROSEC = 1000000;
const qlonglong Mpris2Player::SEEK_DELTA_LIMIT = Mpris2Player::SEC_TO_MICROSEC * 2;

Mpris2Player::Mpris2Player(IPlayer& player, ILocalAlbumArt& localAlbumArt, QObject* parent)
    : QDBusAbstractAdaptor(parent),
      previousPosition(0),
      logger(LoggingManager::instance().getLogger("Mpris2Player")),
      player(player),
      localAlbumArt(localAlbumArt) {
    connect(&player, &IPlayer::playbackStatusChanged, this, &Mpris2Player::onPlaybackStatusChanged);
    connect(&player, &IPlayer::currentSongChanged, this, &Mpris2Player::onSongChanged);
    connect(&player, &IPlayer::positionChanged, this, &Mpris2Player::onPositionChanged);
    connect(&player, &IPlayer::canSeekChanged, this, &Mpris2Player::onCanSeekChanged);
    connect(&player, &IPlayer::canGoNextChanged, this, &Mpris2Player::onCanGoNextChanged);
    connect(&player, &IPlayer::canGoPreviousChanged, this, &Mpris2Player::onCanGoPreviousChanged);
    connect(&player, &IPlayer::volumeChanged, this, &Mpris2Player::onVolumeChanged);

    connect(&localAlbumArt, &ILocalAlbumArt::urlChanged, this, &Mpris2Player::onArtUrlChanged);
}

QString Mpris2Player::playbackStatus() {
    auto retVal = statusToString(player.getPlaybackStatus());
    LOG_TRACE(logger, "playbackStatus() -> " + retVal);
    return retVal;
}

QString Mpris2Player::loopStatus() {
    LOG_TRACE(logger, "loopStatus() -> None");
    return "None";
}

void Mpris2Player::setLoopStatus(const QString&) {
    LOG_TRACE(logger, "setLoopStatus() not implemented");
}

bool Mpris2Player::shuffle() {
    LOG_TRACE(logger, "shuffle() -> false");
    return false;
}

void Mpris2Player::setShuffle(bool) {
    LOG_TRACE(logger, "setShuffle not implemented");
}

double Mpris2Player::volume() {
    auto retVal = player.getVolume();
    LOG_TRACE(logger, "volume() -> " << retVal);
    return retVal;
}

void Mpris2Player::setVolume(double value) {
    LOG_TRACE(logger, "setVolume(" << value << ")");
    player.setVolume(value);
}

QVariantMap Mpris2Player::metadata() {
    LOG_TRACE(logger, "metadata()");
    lastMetadata = toXesam(*player.getCurrentSong());
    return lastMetadata;
}

double Mpris2Player::minimumRate() {
    LOG_TRACE(logger, "minimumRate() -> 1.0");
    return 1.0;
}

double Mpris2Player::maximumRate() {
    LOG_TRACE(logger, "maximumRate() -> 1.0");
    return 1.0;
}

double Mpris2Player::rate() {
    LOG_TRACE(logger, "rate() -> 1.0");
    return 1.0;
}

void Mpris2Player::setRate(float) {
    LOG_TRACE(logger, "setRate() not implemented" );
}

qlonglong Mpris2Player::position() {
    auto pos = static_cast<qlonglong>(player.getPosition()) * SEC_TO_MICROSEC;
    LOG_TRACE(logger, "position() -> " << pos);
    return pos;
}

bool Mpris2Player::canGoNext() {
    auto retVal = player.getCanGoNext();
    LOG_TRACE(logger, "canGoNext() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canGoPrevious() {
    auto retVal = player.getCanGoPrevious();
    LOG_TRACE(logger, "canGoPrevious() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canPlay() {
    LOG_TRACE(logger, "canPlay() -> true");
    return true;
}

bool Mpris2Player::canStop() {
    LOG_TRACE(logger, "canStop() -> false");
    return false;
}

bool Mpris2Player::canPause() {
    LOG_TRACE(logger, "canPause() -> true");
    return true;
}

bool Mpris2Player::canSeek() {
    auto retVal = player.getCanSeek();
    LOG_TRACE(logger, "canSeek() -> " << retVal);
    return retVal;
}

bool Mpris2Player::canControl() {
    LOG_TRACE(logger, "canControl() -> true");
    return true;
}

void Mpris2Player::PlayPause() {
    LOG_TRACE(logger, "PlayPause()");
    player.togglePlayPause();
}

void Mpris2Player::Play() {
    LOG_TRACE(logger, "Play()");
    player.play();
}

void Mpris2Player::Pause() {
    LOG_TRACE(logger, "Pause()");
    player.pause();
}

void Mpris2Player::Stop() {
    LOG_TRACE(logger, "Stop()");
    player.pause();
}

void Mpris2Player::Next() {
    LOG_TRACE(logger, "Next()");
    player.next();
}

void Mpris2Player::Previous() {
    LOG_TRACE(logger, "Previous()");
    player.previous();
}

void Mpris2Player::Seek(qlonglong position) {
    LOG_TRACE(logger, "Seek(" << position << ")");
    qlonglong newPosition = this->position() + position;
    previousPosition = 0; // force emit seeked
    player.seekToPosition(newPosition / SEC_TO_MICROSEC);
}

void Mpris2Player::SetPosition(const QDBusObjectPath&, qlonglong position) {
    LOG_TRACE(logger, "SetPosition(" << position << ")");
    previousPosition = 0; // force emit seeked
    player.seekToPosition(position / SEC_TO_MICROSEC);
}

void Mpris2Player::onPlaybackStatusChanged() {
    LOG_TRACE(logger, "onPlaybackStatusChanged(" + playbackStatus() + ")");
    QVariantMap map;
    map["PlaybackStatus"] = statusToString(player.getPlaybackStatus());
    signalPlayerUpdate(map);
}

void Mpris2Player::onSongChanged(Song* song) {
    LOG_TRACE(logger, "onSongChanged()");
    if (song != nullptr) {
        QVariantMap map;
        map["Metadata"] = toXesam(*song);
        if (map != lastMetadata)
            signalPlayerUpdate(map);
        lastMetadata = map;
        connect(song, &Song::durationChanged, this, &Mpris2Player::onDurationChanged);
    }
}

void Mpris2Player::onArtUrlChanged() {
    LOG_TRACE(logger, "onArtUrlChanged()");
    onSongChanged(player.getCurrentSong());
}

void Mpris2Player::onPositionChanged() {
    qlonglong pos = static_cast<qlonglong>(player.getPosition()) * SEC_TO_MICROSEC;
    if (labs(pos - previousPosition) > SEEK_DELTA_LIMIT || (previousPosition == 0 && pos > 0))
        emit Seeked(pos);
    previousPosition = pos;
}

void Mpris2Player::onDurationChanged() {
    LOG_TRACE(logger, "onDurationChanged()");
    onSongChanged(player.getCurrentSong());
}

void Mpris2Player::onCanSeekChanged() {
    LOG_TRACE(logger, "onCanSeekChanged()");
    QVariantMap map;
    map["CanSeek"] = player.getCanSeek();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoPreviousChanged() {
    LOG_TRACE(logger, "onCanGoPreviousChanged()");
    QVariantMap map;
    map["CanGoPrevious"] = player.getCanGoPrevious();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoNextChanged() {
    LOG_TRACE(logger, "onCanGoNextChanged()");
    QVariantMap map;
    map["CanGoNext"] = player.getCanGoNext();
    signalPlayerUpdate(map);
}

void Mpris2Player::onVolumeChanged() {
    LOG_TRACE(logger, "onVolumeChanged()");
    QVariantMap map;
    map["Volume"] = player.getVolume();
    signalPlayerUpdate(map);
}

QMap<QString, QVariant> Mpris2Player::toXesam(const Song& song) {
    LOG_TRACE(logger, "toXesam('" + song.toString() + "')");
    QMap<QString, QVariant> map;
    if (song.isValid()) {
        QStringList artist;
        artist.append(song.getArtist());
        map["xesam:url"] = song.getTitle();
        map["xesam:artist"] = artist;
        map["xesam:album"] = song.getAlbum();
        map["xesam:title"] = song.getTitle();
        if (song.getDuration())
            map["mpris:length"] = (qlonglong) song.getDuration() * SEC_TO_MICROSEC;
        else
            map["mpris:length"] = 1;
        QString trackId = QString("/org/mpris/MediaPlayer2/Track/%1").arg(song.getUniqueId());
        map["mpris:trackid"] = QVariant(QDBusObjectPath(trackId).path());
        map["mpris:artUrl"] = "file://" + localAlbumArt.getUrl();
    }
    else {
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
    LOG_TRACE(logger, "metadata: {" + qMapToString(map) + "\n}");
    return map;
}

QString Mpris2Player::statusToString(PlaybackStatus status) {
    // a player that is buffering is considered to be paused for mpris, otherwise the player disappear on Plasma 5.
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

void Mpris2Player::signalPlayerUpdate(const QVariantMap& map) {
    LOG_TRACE(logger, "signalPlayerUpdate");
    signalUpdate(map, "org.mpris.MediaPlayer2.Player");
}

void Mpris2Player::signalUpdate(const QVariantMap& map, const QString& interfaceName) {
    LOG_TRACE(logger, "signalUpdate");
    if (!map.isEmpty()) {
        QDBusMessage signal = QDBusMessage::createSignal("/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties",
                                                         "PropertiesChanged");
        QVariantList args = QVariantList() << interfaceName << map << QStringList();
        signal.setArguments(args);

        LOG_TRACE(logger, "PropertiesChanged: {" + qMapToString(map) + "\n}");
        QDBusConnection::sessionBus().send(signal);
    }
}

QString Mpris2Player::qMapToString(const QMap<QString, QVariant>& map) {
    QString output;
    for (auto it = map.begin(); it != map.end(); ++it) {
        // Format output here.
        output += QString("\n\t%1=%2,").arg(it.key()).arg(it.value().toString());
    }
    return output;
}
