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

#include <math.h>
#include <mellowplayer.h>
#include "mpris2player.h"

//---------------------------------------------------------
Mpris2Player::Mpris2Player(QObject *parent):
    QDBusAbstractAdaptor(parent),
    m_length(0),
    m_prevPos(0)
{
    connect(Services::player(), SIGNAL(playbackStatusChanged(PlaybackStatus)),
            this, SLOT(onPlaybackStatusChanged(PlaybackStatus)));
    connect(Services::player(), SIGNAL(songChanged(const SongInfo&)),
            this, SLOT(onSongChanged(const SongInfo&)));
    connect(Services::player(), SIGNAL(artReady(const QString&)),
            this, SLOT(onArtReady(const QString&)));
    connect(Services::player(), SIGNAL(positionChanged(qlonglong)),
            this, SLOT(onPositionChanged(qlonglong)));
    connect(Services::player(), SIGNAL(controlCapsChanged()),
            this, SLOT(onControlCapsChanged()));
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
void Mpris2Player::Seek(qlonglong position)
{
    qDebug() << "Seek " << position;
    Services::player()->seekToPosition(this->position() + position);
}

//---------------------------------------------------------
void Mpris2Player::SetPosition(
        const QDBusObjectPath &trackId, qlonglong position)
{
    position = floor(position / 1000000.f) * 1000000;
    qDebug() << "Changing position of " << trackId.path() << ": "
             << position;
    Services::player()->seekToPosition(position);
}

//---------------------------------------------------------
void Mpris2Player::onPlaybackStatusChanged(PlaybackStatus status)
{
    QVariantMap map;
    map["PlaybackStatus"] = playbackStatusToString(status);
    signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::onSongChanged(const SongInfo &song)
{
    QVariantMap map;
    m_artUrl = "";
    m_length = 0;
    map["Metadata"] = toXesam(song);
    signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::onArtReady(const QString &artFilePathUrl)
{
    QVariantMap map;
    m_artUrl = artFilePathUrl;
    m_artUrl = "file://" + artFilePathUrl;
    map["Metadata"] = toXesam(Services::player()->currentSong());
    signalUpdate(map);
}

//---------------------------------------------------------
void Mpris2Player::onPositionChanged(qlonglong position)
{
    qlonglong floorPos = floor(position / 1000000.f) * 1000000;

    QVariantMap map;
    if(m_length == 0 && Services::player()->currentSong().duration)
    {
        m_length = Services::player()->currentSong().duration;
        map["Metadata"] = toXesam(Services::player()->currentSong());
        signalUpdate(map);
    }
    else
    {
        map["Position"] = floorPos;
        signalUpdate(map);
        qlonglong delta = abs(floorPos - m_prevPos);
        m_prevPos = floorPos;
        if(delta > 2000000)
            emit Seeked(floorPos);
    }
}

//---------------------------------------------------------
void Mpris2Player::onControlCapsChanged()
{
    QVariantMap map;
    map["CanSeek"] = canSeek();
    map["CanPlay"] = canPlay();
    map["CanPause"] = canPause();
    map["CanGoNext"] = canGoNext();
    map["CanGoPrevious"] = canGoPrevious();
    signalUpdate(map);
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
    PlayerInterface* player = Services::player();
    PlaybackStatus status = player->playbackStatus();
    // a player that is buffering is considered to be paused for mpris,
    // othersie the player disappear on Plasma 5.
    if(status == Buffering)
        status = Paused;
    return playbackStatusToString(status);
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
    return toXesam(Services::player()->currentSong());
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
    return m_prevPos;
}

//---------------------------------------------------------
bool Mpris2Player::canGoNext()
{
    return Services::player()->canGoNext();
}

//---------------------------------------------------------
bool Mpris2Player::canGoPrevious()
{
    return Services::player()->canGoPrevious();
}

//---------------------------------------------------------
bool Mpris2Player::canPlay()
{
    return Services::player()->canPlay();
}

//---------------------------------------------------------
bool Mpris2Player::canPause()
{
    return Services::player()->canPlay();
}

//---------------------------------------------------------
bool Mpris2Player::canSeek()
{
    return Services::player()->canSeek();
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
    map["mpris:artUrl"] = m_artUrl;
    return map;
}
