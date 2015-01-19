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
#include <QSystemTrayIcon>
#include <mellowplayer.h>
#include "notifications.h"

//---------------------------------------------------------
NotificationsPlugin::NotificationsPlugin(QObject *parent):
    QObject(parent)
{
}

//---------------------------------------------------------
void NotificationsPlugin::setup()
{
    connect(Services::player(), SIGNAL(songChanged(SongInfo)),
            this, SLOT(onSongChanged(SongInfo)));
    connect(Services::player(), SIGNAL(playbackStatusChanged(PlaybackStatus)),
            this, SLOT(onPlaybackStatusChanged(PlaybackStatus)));
}

//---------------------------------------------------------
void NotificationsPlugin::teardown()
{

}

//---------------------------------------------------------
const PluginMetaData &NotificationsPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Notifications";
    meta.author = "Colin Duquesnoy";
    meta.website = "https://github.com/ColinDuquesnoy/MellowPlayer";
    meta.version = "1.0";
    meta.description =tr("Show playback notifications.");
    return meta;
}

//---------------------------------------------------------
QWidget *NotificationsPlugin::settingsWidget() const
{
    return NULL;
}

//---------------------------------------------------------
void NotificationsPlugin::resetSettings(QWidget *widget) const
{
    Q_UNUSED(widget);
}

//---------------------------------------------------------
void NotificationsPlugin::restoreDefaultSettings(QWidget *widget) const
{
    Q_UNUSED(widget);
}

//---------------------------------------------------------
void NotificationsPlugin::applySettings(QWidget *widget) const
{
    Q_UNUSED(widget);
}

//---------------------------------------------------------
void NotificationsPlugin::onSongChanged(const SongInfo &song)
{
    Services::systemTrayIcon()->showMessage("Mellow Player",
                                            song.toString());
}

void NotificationsPlugin::onPlaybackStatusChanged(PlaybackStatus status)
{
    switch (status) {
    case Paused:
        Services::systemTrayIcon()->showMessage("Mellow Player",
                                                tr("Pause"));
        break;
    default:
        break;
    }
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2( NotificationsPlugin, NotificationsPlugin )
#endif
