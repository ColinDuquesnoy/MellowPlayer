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

#include <QCheckBox>
#include <QLayoutItem>
#include <QVBoxLayout>
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
    meta.description =tr("Display playback notifications");
    return meta;
}

//---------------------------------------------------------
QWidget *NotificationsPlugin::settingsWidget() const
{
    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setMargin(0);

    QCheckBox* cb = new QCheckBox(tr("Display a notification when the current track has changed"));
    cb->setChecked(QSettings().value("notifySongChanged", true).toBool());
    layout->addWidget(cb);
    cb = new QCheckBox(tr("Display a notification when the playback has paused"));
    cb->setChecked(QSettings().value("notifyPaused", true).toBool());
    layout->addWidget(cb);
    cb = new QCheckBox(tr("Display a notification when the playback has stopped"));
    cb->setChecked(QSettings().value("notifyStopped", true).toBool());
    layout->addWidget(cb);
    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    return widget;
}

//---------------------------------------------------------
void NotificationsPlugin::resetSettings(QWidget *widget) const
{
    QCheckBox* cb = qobject_cast<QCheckBox*>(widget->layout()->itemAt(0)->widget());
    cb->setChecked(QSettings().value("notifySongChanged", true).toBool());
    cb = qobject_cast<QCheckBox*>(widget->layout()->itemAt(1)->widget());
    cb->setChecked(QSettings().value("notifyPaused", true).toBool());
    cb = qobject_cast<QCheckBox*>(widget->layout()->itemAt(2)->widget());
    cb->setChecked(QSettings().value("notifyStopped", true).toBool());
}

//---------------------------------------------------------
void NotificationsPlugin::restoreDefaultSettings() const
{
    QSettings().setValue("notifySongChanged", true);
    QSettings().setValue("notifyPaused", true);
    QSettings().setValue("notifyStopped", true);
}

//---------------------------------------------------------
void NotificationsPlugin::applySettings(QWidget *widget) const
{
    QCheckBox* cb = qobject_cast<QCheckBox*>(widget->layout()->itemAt(0)->widget());
    QSettings().setValue("notifySongChanged", cb->isChecked());
    cb = qobject_cast<QCheckBox*>(widget->layout()->itemAt(1)->widget());
    QSettings().setValue("notifyPaused", cb->isChecked());
    cb = qobject_cast<QCheckBox*>(widget->layout()->itemAt(2)->widget());
    QSettings().setValue("notifyStopped", cb->isChecked());
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
    Q_UNUSED(art);
    m_artReady = true;
    notifySongChange();
}

//---------------------------------------------------------
void NotificationsPlugin::onPlaybackStatusChanged(PlaybackStatus status)
{
    switch(status){
    case Paused:
        if(m_wasPlaying && QSettings().value("notifyPaused").toBool())
            Services::trayIcon()->showMessage(tr("Paused"));
        m_wasPlaying = false;
        break;
    case Stopped:
        if(QSettings().value("notifyStopped").toBool())
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
        if(QSettings().value("notifySongChanged").toBool())
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
