//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include "utils/mpris_utils.h"

//-------------------------------------
void signalPlayerUpdate(const QVariantMap &map) {
  signalUpdate(map, "org.mpris.MediaPlayer2.Player");
}

//-------------------------------------
void signalUpdate(const QVariantMap &map, const QString &interfaceName) {
  if (map.isEmpty()) {
    return;
  }
  QDBusMessage signal = QDBusMessage::createSignal(
      "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties",
      "PropertiesChanged");
  QVariantList args = QVariantList() << interfaceName << map << QStringList();
  signal.setArguments(args);

  qDebug() << "MPRIS-PropertiesChanged:" << map;
  QDBusConnection::sessionBus().send(signal);
}
