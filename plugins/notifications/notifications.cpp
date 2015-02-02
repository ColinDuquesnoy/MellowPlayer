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
    QObject(parent)
{
}

//---------------------------------------------------------
void NotificationsPlugin::setup()
{
    connect(Services::player(), SIGNAL(artReady(QString)),
            this, SLOT(onArtReady(QString)));
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
void NotificationsPlugin::onArtReady(const QString &art)
{
    SongInfo song = Services::player()->currentSong();
    if(song.isValid())
    {
        Services::trayIcon()->showMessage(song.toString(), art);
    }
}

//---------------------------------------------------------
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2( NotificationsPlugin, NotificationsPlugin )
#endif
