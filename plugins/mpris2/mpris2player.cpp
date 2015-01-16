//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include <mellowplayer.h>
#include "mpris2player.h"

//---------------------------------------------------------
Mpris2Player::Mpris2Player(QObject *parent):
    QDBusAbstractAdaptor(parent)
{
    connect(Services::player(), SIGNAL(playbackStatusChanged(PlaybackStatus)),
            this, SLOT(onPlaybackStatusChanged(PlaybackStatus)));
    connect(Services::player(), SIGNAL(songChanged(const SongInfo&)),
            this, SLOT(onSongChanged(const SongInfo&)));
    connect(Services::player(), SIGNAL(artReady(const QString&)),
            this, SLOT(onArtReady(const QString&)));
    connect(Services::player(), SIGNAL(positionChanged(int)),
            this, SLOT(onPositionChanged(int)));
}

//---------------------------------------------------------
void Mpris2Player::PlayPause()
{
    Services::player()->playPause();
}

//---------------------------------------------------------
void Mpris2Player::Play()
{
    Services::player()->playPause();
}

//---------------------------------------------------------
void Mpris2Player::Pause()
{
    Services::player()->playPause();
}

//---------------------------------------------------------
void Mpris2Player::Stop()
{
    Services::player()->stop();
}

//---------------------------------------------------------
void Mpris2Player::Next()
{
    Services::player()->next();
}

//---------------------------------------------------------
void Mpris2Player::Previous()
{
    Services::player()->previous();
}

//---------------------------------------------------------
void Mpris2Player::Seek(int position)
{
    Services::player()->seekToPosition(this->position() + position);
}

//---------------------------------------------------------
void Mpris2Player::SetPosition(
        const QDBusObjectPath &trackId, qlonglong position)
{
    qDebug() << "Changing position of " << trackId.path();
    Services::player()->seekToPosition(position);
}

//---------------------------------------------------------
void Mpris2Player::onPlaybackStatusChanged(PlaybackStatus status)
{
    QVariantMap map;
    map["PlaybackStatus"] = playbackStatusToString(status, false);
    this->signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::onSongChanged(const SongInfo &song)
{
    QVariantMap map;
    this->artUrl = "";
    map["Metadata"] = this->toXesam(song);
    this->signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::onArtReady(const QString &artFilePathUrl)
{
    QVariantMap map;
    this->artUrl = artFilePathUrl;
    map["Metadata"] = this->toXesam(Services::player()->currentSong());
    this->signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::onPositionChanged(int position)
{
    QVariantMap map;
    map["Position"] = position;
    map["Metadata"] = this->toXesam(Services::player()->currentSong());
    this->signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::signalUpdate(const QVariantMap &map)
{
    if (map.isEmpty()) {
        return;
    }
    QDBusMessage signal = QDBusMessage::createSignal(
        "/org/mpris/MediaPlayer2",
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged");
    QVariantList args = QVariantList()
        << "org.mpris.MediaPlayer2.Player"
        << map
        << QStringList();
    signal.setArguments(args);
    QDBusConnection::sessionBus().send(signal);
}

//---------------------------------------------------------
QString Mpris2Player::playbackStatus()
{
    SongInfo song = Services::player()->currentSong();
    QString retVal = "Stopped";
    if(song.isValid())
        retVal = playbackStatusToString(song.playbackStatus, false);
    return retVal;
}

//---------------------------------------------------------
QString Mpris2Player::loopStatus()
{
    return "None";
}

//---------------------------------------------------------
void Mpris2Player::setLoopStatus(const QString &status)
{
    qDebug() << "Mpris2Player.SetLoopStatus not implemented yet: " << status;
}

//---------------------------------------------------------
bool Mpris2Player::shuffle()
{
    return false;
}

//---------------------------------------------------------
void Mpris2Player::setShuffle(bool value)
{
    qDebug() << "Mpris2Player.SetShuffle not implemented yet: " << value;
}

//---------------------------------------------------------
float Mpris2Player::volume()
{
    return Services::player()->volume();
}

//---------------------------------------------------------
void Mpris2Player::setVolume(float value)
{
    Services::player()->setVolume(value);
}

//---------------------------------------------------------
QVariantMap Mpris2Player::metadata()
{
    return this->toXesam(Services::player()->currentSong());
}

//---------------------------------------------------------
float Mpris2Player::minimumRate()
{
    return 1.0f;
}

//---------------------------------------------------------
float Mpris2Player::maximumRate()
{
    return 1.0f;
}

//---------------------------------------------------------
float Mpris2Player::rate()
{
    return 1.0f;
}

//---------------------------------------------------------
void Mpris2Player::setRate(float value)
{
    qDebug() << "changing playback rate is not supported: " << value;
}

//---------------------------------------------------------
qlonglong Mpris2Player::position()
{
    return Services::player()->currentSong().position;
}

//---------------------------------------------------------
bool Mpris2Player::canGoNext()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Player::canGoPrevious()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Player::canPlay()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Player::canPause()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Player::canSeek()
{
    return true;
}

//---------------------------------------------------------
bool Mpris2Player::canControl()
{
    return true;
}

//---------------------------------------------------------
QMap<QString, QVariant> Mpris2Player::toXesam(const SongInfo &song)
{
    QMap<QString, QVariant> map;
    if(song.isValid())
    {
        QStringList artist; artist.append(song.artistName);
        map["xesam:artist"] = artist;
        map["xesam:album"] = song.albumName;
        map["xesam:title"] = song.songName;
        map["mpris:length"] = song.duration;
        QString trackId = QString(
            "/org/mpris/MediaPlayer2/Track/%1").arg(song.songId);
        map["mpris:trackid"] = QVariant(QDBusObjectPath(trackId).path());
    }
    else
    {
        QStringList artist; artist.append("");
        map["xesam:artist"] = artist;
        map["xesam:album"] = "";
        map["xesam:title"] = "";
        map["mpris:length"] = 0;
        map["mpris:trackid"] = QVariant(QDBusObjectPath(
                    "/org/mpris/MediaPlayer2/NoTrack").path());
    }
    map["mpris:artUrl"] = this->artUrl;
    return map;
}
