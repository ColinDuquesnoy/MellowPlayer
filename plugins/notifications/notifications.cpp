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

#include <QWidget>
#include <mellowplayer.h>
#include "notifications.h"

//---------------------------------------------------------
NotificationsPlugin::NotificationsPlugin(QObject *parent):
    QObject(parent),
    m_wasPlaying(false),
    m_songStarted(false),
    m_artReady(false)
{
}

//---------------------------------------------------------
void NotificationsPlugin::setup()
{
    connect(Services::player(), SIGNAL(artReady(QString)),
            this, SLOT(onArtReady(QString)));
    connect(Services::player(), SIGNAL(songStarted(SongInfo)),
            this, SLOT(onSongStarted(SongInfo)));
    connect(Services::player(), SIGNAL(playbackStatusChanged(PlaybackStatus)),
            this, SLOT(onPlaybackStatusChanged(PlaybackStatus)));
}

//---------------------------------------------------------
const PluginMetaData &NotificationsPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Notifications";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "https://github.com/ColinDuquesnoy";
    meta.version = "1.0";
    meta.description =tr("Shows a notification when the song changed.");
    return meta;
}

//---------------------------------------------------------
void NotificationsPlugin::onSongStarted(const SongInfo &song)
{
    if(song.isValid())
        m_songStarted = true;
    notifySongChange();
}

//---------------------------------------------------------
void NotificationsPlugin::onArtReady(const QString &art)
{
    m_artReady = true;
    notifySongChange();
}

//---------------------------------------------------------
void NotificationsPlugin::onPlaybackStatusChanged(PlaybackStatus status)
{
    switch(status){
    case Paused:
        if(m_wasPlaying)
            Services::trayIcon()->showMessage(tr("Paused"));
        m_wasPlaying = false;
        break;
    case Stopped:
        Services::trayIcon()->showMessage(tr("Stopped"));
        m_wasPlaying = false;
        break;
    case Playing:
        m_wasPlaying = true;
        break;
    case Buffering:
    default:
        m_wasPlaying = false;
        break;
    }
}

//---------------------------------------------------------
void NotificationsPlugin::notifySongChange()
{
    if(m_songStarted && m_artReady)
    {
        Services::trayIcon()->showMessage(
            Services::player()->currentSong().toString(),
            Services::player()->currentArt());
        m_songStarted = false;
        m_artReady = false;
    }
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2( NotificationsPlugin, NotificationsPlugin )
#endif
