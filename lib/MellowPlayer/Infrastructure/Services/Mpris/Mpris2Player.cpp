#include "Mpris2Player.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

#define SEC_TO_MICROSEC 1000000.0
#define SEEK_DELTA_LIMIT SEC_TO_MICROSEC * 2

Mpris2Player::Mpris2Player(IPlayer& player, UseCases::LocalAlbumArtService& localAlbumArt, QObject* parent)
    : QDBusAbstractAdaptor(parent), player(player), localAlbumArt(localAlbumArt) {
    connect(&player, &IPlayer::playbackStatusChanged, this, &Mpris2Player::onPlaybackStatusChanged);
    connect(&player, &IPlayer::currentSongChanged, this, &Mpris2Player::onSongChanged);
    connect(&player, &IPlayer::positionChanged, this, &Mpris2Player::onPositionChanged);
    connect(&player, &IPlayer::canSeekChanged, this, &Mpris2Player::onCanSeekChanged);
    connect(&player, &IPlayer::canGoNextChanged, this, &Mpris2Player::onCanGoNextChanged);
    connect(&player, &IPlayer::canGoPreviousChanged, this, &Mpris2Player::onCanGoPreviousChanged);
    connect(&player, &IPlayer::volumeChanged, this, &Mpris2Player::onVolumeChanged);

    connect(&localAlbumArt, &LocalAlbumArtService::urlChanged, this, &Mpris2Player::onArtUrlChanged);
}

QString Mpris2Player::playbackStatus() { return statusToString(player.getPlaybackStatus()); }

QString Mpris2Player::loopStatus() { return "None"; }

void Mpris2Player::setLoopStatus(const QString&) {}

bool Mpris2Player::shuffle() { return false; }

void Mpris2Player::setShuffle(bool) {}

double Mpris2Player::volume() { return player.getVolume(); }

void Mpris2Player::setVolume(double value) { player.setVolume(value); }

QVariantMap Mpris2Player::metadata() {
    lastMetadata = toXesam(*player.getCurrentSong());
    return lastMetadata;
}

double Mpris2Player::minimumRate() { return 1.0; }

double Mpris2Player::maximumRate() { return 1.0; }

double Mpris2Player::rate() { return 1.0; }

void Mpris2Player::setRate(float) {}

qlonglong Mpris2Player::position() { return static_cast<qlonglong>(player.getPosition() * SEC_TO_MICROSEC); }

bool Mpris2Player::canGoNext() { return player.getCanGoNext(); }

bool Mpris2Player::canGoPrevious() { return player.getCanGoPrevious(); }

bool Mpris2Player::canPlay() { return true; }

bool Mpris2Player::canStop() { return false; }

bool Mpris2Player::canPause() { return true; }

bool Mpris2Player::canSeek() { return player.getCanSeek(); }

bool Mpris2Player::canControl() { return true; }

void Mpris2Player::PlayPause() { player.togglePlayPause(); }

void Mpris2Player::Play() { player.play(); }

void Mpris2Player::Pause() { player.pause(); }

void Mpris2Player::Stop() { player.pause(); }

void Mpris2Player::Next() { player.next(); }

void Mpris2Player::Previous() { player.previous(); }

void Mpris2Player::Seek(qlonglong position) {
    qlonglong newPosition = this->position() + position;
    previousPosition = 0; // force emit seeked
    player.seekToPosition(newPosition / SEC_TO_MICROSEC);
}

void Mpris2Player::SetPosition(const QDBusObjectPath&, qlonglong position) {
    previousPosition = 0; // force emit seeked
    player.seekToPosition(position / SEC_TO_MICROSEC);
}

void Mpris2Player::onPlaybackStatusChanged() {
    QVariantMap map;
    map["PlaybackStatus"] = statusToString(player.getPlaybackStatus());
    signalPlayerUpdate(map);
}

void Mpris2Player::onSongChanged(Song* song) {
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
    onSongChanged(player.getCurrentSong());
}

void Mpris2Player::onPositionChanged() {
    auto pos = static_cast<qlonglong>(player.getPosition() * SEC_TO_MICROSEC);
    if (abs(pos - previousPosition) > SEEK_DELTA_LIMIT || (previousPosition == 0 && pos > 0))
        emit Seeked(pos);
    previousPosition = pos;
}

void Mpris2Player::onDurationChanged() {
    onSongChanged(player.getCurrentSong());
}

void Mpris2Player::onCanSeekChanged() {
    QVariantMap map;
    map["CanSeek"] = player.getCanSeek();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoPreviousChanged() {
    QVariantMap map;
    map["CanGoPrevious"] = player.getCanGoPrevious();
    signalPlayerUpdate(map);
}

void Mpris2Player::onCanGoNextChanged() {
    QVariantMap map;
    map["CanGoNext"] = player.getCanGoNext();
    signalPlayerUpdate(map);
}

void Mpris2Player::onVolumeChanged() {
    QVariantMap map;
    map["Volume"] = player.getVolume();
    signalPlayerUpdate(map);
}

QMap<QString, QVariant> Mpris2Player::toXesam(const Song& song) {
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

    return map;
}

QString Mpris2Player::statusToString(IPlayer::PlaybackStatus status) {
    // a player that is buffering is considered to be paused for mpris, otherwise the player disappear on Plasma 5.
    if (status == IPlayer::PlaybackStatus::Buffering)
        status = IPlayer::PlaybackStatus::Paused;
    switch (status) {
        case IPlayer::PlaybackStatus::Playing:
            return "Playing";
        case IPlayer::PlaybackStatus::Paused:
            return "Paused";
        default:
            return "Stopped";
    }
}

void Mpris2Player::signalPlayerUpdate(const QVariantMap& map) { signalUpdate(map, "org.mpris.MediaPlayer2.Player"); }

void Mpris2Player::signalUpdate(const QVariantMap& map, const QString& interfaceName) {
    if (!map.isEmpty()) {
        QDBusMessage signal = QDBusMessage::createSignal("/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties",
                                                         "PropertiesChanged");
        QVariantList args = QVariantList() << interfaceName << map << QStringList();
        signal.setArguments(args);

        qDebug() << "MPRIS-PropertiesChanged:" << map;
        QDBusConnection::sessionBus().send(signal);
    }
}
