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
#include <QtDBus>
#include <mellowplayer.h>
#include "gnomemediakeys.h"
#include "mediakeys_interface.h"

#define GSD_SERVICE "org.gnome.SettingsDaemon"
#define GSD_PATH "/org/gnome/SettingsDaemon/MediaKeys"
#define GSD_INTERFACE = "org.gnome.SettingsDaemon.MediaKeys"

//---------------------------------------------------------
GnomemediakeysPlugin::GnomemediakeysPlugin(QObject *parent):
    QObject(parent),
    m_interface(NULL),
    m_connected(false)
{
}

//---------------------------------------------------------
void GnomemediakeysPlugin::setup()
{
#ifdef __kde_support__
    return; // not needed on KDE
#else
    qDebug() << "registering gnome settings daemon";
    if (!QDBusConnection::sessionBus().interface()->isServiceRegistered(GSD_SERVICE))
    {
        qWarning() << "gnome settings daemon not registered";
        return;
    }
    m_interface = new OrgGnomeSettingsDaemonMediaKeysInterface(
        GSD_SERVICE, GSD_PATH, QDBusConnection::sessionBus(), this);
    QDBusPendingReply<> reply = m_interface->GrabMediaPlayerKeys(
        QCoreApplication::applicationName(),
        QDateTime::currentDateTime().toTime_t());
    QDBusPendingCallWatcher* watcher = new QDBusPendingCallWatcher(reply, this);
    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
            this, SLOT(registerFinished(QDBusPendingCallWatcher*)));
#endif
}

//---------------------------------------------------------
void GnomemediakeysPlugin::teardown()
{
    // Check if the GSD service is available
    if (!QDBusConnection::sessionBus().interface()->isServiceRegistered(GSD_SERVICE))
        return;
    if (!m_interface || !m_connected)
        return;

    m_connected = false;

    m_interface->ReleaseMediaPlayerKeys(QCoreApplication::applicationName());
    disconnect(m_interface, SIGNAL(MediaPlayerKeyPressed(QString,QString)),
               this, SLOT(gnomeMediaKeyPressed(QString,QString)));
}

//---------------------------------------------------------
const PluginMetaData &GnomemediakeysPlugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "Gnomemediakeys";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "https://github.com/ColinDuquesnoyE";
    meta.version = "1.0";
    meta.description =tr("Add support for gnome multimedia keys daemon");
    return meta;
}

//---------------------------------------------------------
void GnomemediakeysPlugin::registerFinished(QDBusPendingCallWatcher *watcher)
{
    QDBusMessage reply = watcher->reply();
    watcher->deleteLater();

    if (reply.type() == QDBusMessage::ErrorMessage) {
      qWarning() << "Failed to grab media keys"
                 << reply.errorName() <<reply.errorMessage();
      return;
    }

    connect(m_interface, SIGNAL(MediaPlayerKeyPressed(QString,QString)),
            this, SLOT(gnomeMediaKeyPressed(QString,QString)));

    m_connected = true;
    qDebug() << "gnome settings daemon registered";
}

//---------------------------------------------------------
void GnomemediakeysPlugin::gnomeMediaKeyPressed(const QString& _, const QString& key)
{
    Q_UNUSED(_);
    if (key == "Play")
        Services::player()->playPause();
    if (key == "Next")
        Services::player()->next();
    if (key == "Previous")
        Services::player()->previous();
}
